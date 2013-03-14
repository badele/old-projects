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
 
 


//$site = getSiteID(5); //stecas
/*$site = getSiteID(8); //jesuislibre
InsertPage($site['site_id'],$site['url']);
db_updateAllPageState('crawled',0);
*/

// Ajoute les pages des sites
db_insertPageFromSite();
while (1) {
	crawl();
	extractLinks();
	addTaskPageAll();
	extractWords();
	showInformation('wait all');
	//sleep($GLOBALS['wait_process']);
}

showError();
	
?>
