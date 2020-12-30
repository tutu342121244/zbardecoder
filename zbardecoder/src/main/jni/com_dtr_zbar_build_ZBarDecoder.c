#include <string.h>
#include <stdlib.h>
#include <android/log.h>
#include <stdio.h>

#include "zbar.h"

#include "com_dtr_zbar_build_ZBarDecoder.h"

JNIEXPORT jstring JNICALL Java_com_dtr_zbar_build_ZBarDecoder_decodeRaw(
		JNIEnv *env, jobject obj, jbyteArray img, jint width, jint height) {

    __android_log_print(ANDROID_LOG_ERROR, "zbar2", "decodeRaw start");
	zbar_image_scanner_t *scanner;
	zbar_image_t *zimage;
	zbar_image_t *zgrayimage;

	jbyte *pixbuf;
	jstring s = NULL;

	zbar_set_verbosity(10); // XXX

	pixbuf = (*env)->GetByteArrayElements(env, img, 0);

	zimage = zbar_image_create();
	if (zimage == NULL) {
		(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
		return NULL;
	}

	zbar_image_set_format(zimage, *(unsigned long *) "Y800");
	zbar_image_set_size(zimage, width, height);
	zbar_image_set_data(zimage, pixbuf, (*env)->GetArrayLength(env, img),
			zbar_image_free_data);

	zgrayimage = zbar_image_convert(zimage, *(unsigned long *) "Y800");
	if (zgrayimage == NULL) {
		(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
		return NULL;
	}

	zbar_image_destroy(zimage);

	scanner = zbar_image_scanner_create();
	zbar_image_scanner_set_config(scanner, 0, ZBAR_CFG_ENABLE, 1);
	zbar_scan_image(scanner, zgrayimage);

	const zbar_symbol_t *sym;

	sym = zbar_image_first_symbol(zgrayimage);
	if (sym != NULL) {
		const char *sym_data;
		sym_data = zbar_symbol_get_data(sym);
		s = (*env)->NewStringUTF(env, sym_data);
	}

	(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
	return s;
}

JNIEXPORT jstring JNICALL Java_com_dtr_zbar_build_ZBarDecoder_decodeCrop(
		JNIEnv *env, jobject obj, jbyteArray img, jint width, jint height,
		jint x, jint y, jint cropw, jint croph) {

	__android_log_print(ANDROID_LOG_ERROR, "zbar", "decodeCrop start width=%d height=%d", cropw, croph);
	zbar_image_scanner_t *scanner;
	zbar_image_t *zimage;
	zbar_image_t *zgrayimage;

	jbyte *pixbuf;
	jstring s = NULL;
    jbyteArray jarrRV = NULL;

	zbar_set_verbosity(10); // XXX

	pixbuf = (*env)->GetByteArrayElements(env, img, 0);

	zimage = zbar_image_create();
	if (zimage == NULL) {
		(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
		return NULL;
	}

	zbar_image_set_format(zimage, *(unsigned long *) "Y800");
	zbar_image_set_size(zimage, width, height);
	zbar_image_set_data(zimage, pixbuf, (*env)->GetArrayLength(env, img),
			zbar_image_free_data);

	zbar_image_set_crop(zimage, x, y, cropw, croph);

	zgrayimage = zbar_image_convert(zimage, *(unsigned long *) "Y800");
	if (zgrayimage == NULL) {
		(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
		return NULL;
	}

	zbar_image_destroy(zimage);

	scanner = zbar_image_scanner_create();
	zbar_image_scanner_set_config(scanner, 0, ZBAR_CFG_ENABLE, 1);
	zbar_scan_image(scanner, zgrayimage);

	const zbar_symbol_t *sym;

	sym = zbar_image_first_symbol(zgrayimage);
	if (sym != NULL) {
		const char *sym_data;
		sym_data = zbar_symbol_get_data(sym);
		s = (*env)->NewStringUTF(env, sym_data);
	}

	(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
	return s;
}


