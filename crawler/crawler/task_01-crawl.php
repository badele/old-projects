<?php
/*
 * Created on 13 juin 08
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */
 
 include 'database.php';
 include 'fonctions.php';
 include 'tasks.php';
 include 'queue.php';
 
 
// Charge les infos du site

/*$site = getSite('http://www.jesuislibre.org/');
bl_InsertPage($site['site_id'],$site['url']);
db_updateAllPageState('crawled',0);*/

// Ajoute les pages des sites


crawlAll1();
exit;

db_insertPageFromSite();
while (1) {
	crawlAll1();
	showElapsedTime("link wait<br>");
	sleep($GLOBALS['wait_process']);
}


?>
