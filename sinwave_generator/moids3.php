<html>
<head>
<title>damonde C-code genarator 3 </title>
</head>
<body>
‚·‚Î‚ç‚µ‚«’P‰¹‚Ì¢ŠE
<form action="moids3.php" method=post>

‚È‚éü”g”
<br> <input type="text" name="basefreq">
<br />
‚È‚éŠÔ:[sec]
<br> <input type="text" name="time">
<input type="submit" name="submit" value="generate">
</form>
<?php
$fs = 31250.0;
$PI = 3.14159;


$basefreq = $_POST['basefreq'];
$ratio = $_POST['ratio'];
print "<br /> <br />";
print "<h2>generated code</h2>";

printf("#define TIME_CNT %d<br />",$time*31250);
$numindex = 1;


printf("<br />");
print "char fa_list[NUMINDEX] = {";
for ($i=1; $i<(int)$numindex+1; $i++){

	  $a = -2.0 * cos( (2.0 * $PI * (float)$i * (float)$basefreq) / 31250.0);
	  
	  
	  $fa = $a * 64.0;
	  printf("%d, ",$fa);
	  //printf("%f", cos( (2.0 * $PI * (float)$i * (float)$base) / 31250.0));
  }
 
printf("};");

printf("<br />");
print "char fb_list[NUMINDEX] = {";
for ($i=1; $i<(int)$numindex+1; $i++){

	  $b = -cos( (2.0 * $PI * (float)$i * (float)$basefreq) / 31250.0);
	  
	  if ($b == -64) {printf("‚»‚Ìü”g”‚Í’á‚·‚¬‚Ä–³—‚Å‚·EEE"); die;}
	  
	  $fb = $b * 64.0;
	  printf("%d, ",$fb);
	  //printf("%f", cos( (2.0 * $PI * (float)$i * (float)$base) / 31250.0));
  }
 
printf("};");


  //$b = -cos(2.0*PI*i*base*mag / (double)fs);
?>
</body>
</html>