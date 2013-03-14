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

/*
 * select page.page_id,link.link_id,word from temp_link_from inner join link on link.link=temp_link_from.url left join page on page.url=link.link

 * 
 */

db_Rollback();
while (1) {
	extractLinksAll();
	showInformation("link wait<br>");
	//sleep($GLOBALS['wait_process']);
}

?>
