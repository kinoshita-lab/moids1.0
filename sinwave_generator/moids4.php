<html>
<head>
<title>damonde C-code genarator 4 </title>
</head>
<body>
音出せ！
<form action="moids4.php" method=post>

なる周波数 [Hz]
<br>
<input type="text" name="freq1">　
<input type="text" name="freq2">　
<input type="text" name="freq3">
<br />
なる時間 [ms]
<br> <input type="text" name="time">
<br />
<input type="submit" name="submit" value="generate!!">
</form>
<?php
$FS = 31250.0;
$PI = 3.14159;

$time = $_POST['time'];
$time_cnt = (int)(($time / 1000) * $FS);
$f1 = $_POST['freq1'];
$f2 = $_POST['freq2'];
$f3 = $_POST['freq3'];
$flist = array($f1, $f2, $f3);
$nS1 = (int)$FS / $f1;
$nS2 = (int)$FS / $f2;
$nS3 = (int)$FS / $f3;

print "<h2>生成結果</h2>\n";

printf("%d[Hz] ------&gt; %f[Hz] <br />\n", $f1, $FS / (int)$nS1);
print "<br />";
printf("%d[Hz] ------&gt; %f[Hz] <br />\n", $f2, $FS / (int)$nS2);
print "<br />";
printf("%d[Hz] ------&gt; %f[Hz] <br />\n", $f3, $FS / (int)$nS3);
print "<br />";
printf("%d[ms] ------&gt; %f[ms] <br />\n", $time, 1000 * (int)($time_cnt) / $FS);
print "<br />";

print "<br /> <br />";
print "<h2>generated code</h2>";
print "ここから下をコピペしてね♪";
print "<hr />";
printf("#define TIME_CNT %d<br />", $time_cnt);
printf("#define NUMSAMPLE0 %d<br />", $nS1);
printf("#define NUMSAMPLE1 %d<br />", $nS2);
printf("#define NUMSAMPLE2 %d<br />", $nS3);


printf("<br />\n");

    printf("unsigned char sample0[NUMSAMPLE0] = {");
    for ($i=0; $i< $nS1 -1; $i++){
	printf("%d,", 127 + 127*sin(2*$PI*$f1*$i/$FS));
    }
    printf("};\n");
printf("<br />\n");

    printf("unsigned char sample1[NUMSAMPLE1] =\n{");
    for ($i=0; $i< $nS2 -1 ; $i++){
	printf("%d,", 127 + 127*sin(2*$PI*$f2*$i/$FS));
    }
    printf("};\n");
printf("<br />\n");

    printf("unsigned char sample2[NUMSAMPLE2] =\n{");
    for ($i=0; $i< $nS3 -1; $i++){
	printf("%d,", 127 + 127*sin(2*$PI*$f3*$i/$FS));
    }
    printf("};\n");
printf("<br />\n");

?>
</body>
</html>