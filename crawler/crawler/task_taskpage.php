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
  
 
// Charge les infos du site

//db_updateAllLinkState(0);
while (1) {
	// Ajoute les pages des sites
	db_insertPageFromSite();

	showInformation(addTaskPageAll()." pages inserted<br>");
	sleep(600);
}

?>
