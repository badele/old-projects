<?php
/*
 * Created on 13 juin 08
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */
 
 include 'conf.php';
 
 include '../commons/database.php';
 
 
 include "../client/database/db_link.php";
 include "../client/database/bl_link.php";

 
 $link = bl_GetNextLinkTemp();
 while ($link)
 {
	$link = $link['link'];
	print "$link<br>"; 
 	$link = bl_GetNextLinkTemp();
 }
 

?>
