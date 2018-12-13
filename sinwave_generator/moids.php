<html>
<head>
<title>damonde C-code genarator</title>
</head>
<body>

<form action="moids.php" method=post>

base freq
<br> <input type="text" name="basefreq">

<p> ratio
<br><input type="text" name="ratio">
<p>

<input type="submit" name="submit" value="generate">
</form>
<?php
$fs = 31250.0;
$PI = 3.14159;


$basefreq = $_POST['basefreq'];
$ratio = $_POST['ratio'];
print "<br /> <br />";
print "<h2>generated code</h2>";

$numindex = ($fs / (2.0 * $basefreq * $ratio));
printf("#define NUMINDEX %d<br />",$numindex+1);
printf("<br />");
print "char fa_list[NUMINDEX] = {";
for ($i=1; $i<(int)$numindex+1; $i++){

	  $a = -2.0 * cos( (2.0 * $PI * (float)$i * (float)$basefreq * $ratio) / 31250.0);
	  
	  
	  $fa = $a * 64.0;
	  printf("%d, ",$fa);
	  //printf("%f", cos( (2.0 * $PI * (float)$i * (float)$base * $ratio) / 31250.0));
  }
 
printf("};");

printf("<br />");
print "char fb_list[NUMINDEX] = {";
for ($i=1; $i<(int)$numindex+1; $i++){

	  $b = -cos( (2.0 * $PI * (float)$i * (float)$basefreq * $ratio) / 31250.0);
	  
	  
	  $fb = $b * 64.0;
	  printf("%d, ",$fb);
	  //printf("%f", cos( (2.0 * $PI * (float)$i * (float)$base * $ratio) / 31250.0));
  }
 
printf("};");


  //$b = -cos(2.0*PI*i*base*mag / (double)fs);
?>
</body>
</html>