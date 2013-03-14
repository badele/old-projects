<HTML>
<HEAD>
		<title>Motte - Search Engine</title>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
		<meta name="keywords" content="Motte Search Engine">
		<meta name="description" content="Moteur de recherche Motte">
		<link href="style1.css" rel="stylesheet" type="text/css">
</HEAD>

<BODY>

<?php
/*
 * Created on 12 juil. 08
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */
 
 include 'database.php';
 include 'fonctions.php';

$query = $_GET['q'];
$queries = split(" ",$query);

//print strongKeyword($queries,"Wikipédia:Atelier graphique/Logiciels - Wikipédia");
//exit;


$results = db_searchPages($query,1);


$html = '<dl>';
foreach ($results as $item) {
	$url = $item['url'];
	$title = strongKeyword($queries,substr($item['title'],0,76));
	
	$html .= "<dt><a href='$url'>$title</a></dt>";
	$html .= "<dd>Description</dd>";
} 
$html .= '<dl>';

print $html;
 
?>
</html>