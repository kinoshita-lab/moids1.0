<html>
<head>
<title>damonde C-code genarator 2</title>
</head>
<body>

<form action="moids2.php" method=post>

‚È‚éŠÔ:[sec]
<br> <input type="text" name="time">

<input type="submit" name="submit" value="generate">
</form>
<?php
$fs = 31250;

printf("#define TIME_CNT %d<br />",$time*31250);
?>
</body>
</html>