# zbardecoder

ZBarSDK 解决arm64，arm7s，中文乱码问题：

问题一： 修改指定qrdectxt.c 中 iconv_open "ISO8859-1"编码为 "GB18030" 问题导致的解码问题；

在sourceforge下载zbar源码，修改了文件
zbar/qrcode/qrdectxt.c
// 重点在这里，我们不要 ISO8859-1，直接换成 GB18030 就可以了
  //latin1_cd=iconv_open("UTF-8","ISO8859-1");
  latin1_cd=iconv_open("UTF-8","GB18030");


问题一： 针对 office 使用Excel自定义函数QRCode(text,[width])在Excel文件中生成二维码 , decoder解码中文乱码问题:
   注：问题的本质是生成二维码的编码方式为GBK 或GBK版本系列的编码，而使用zbar解码出现的乱码问题
   
   本项目重点解决的问题加入了decoder
   
   
