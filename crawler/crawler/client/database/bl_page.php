<?php
/*
 * Created on 21 juin 08
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */
 
 function bl_InsertPage($site_id,$url)
 {
 	$page = db_getPagebyURL($url);
 	if (!$page) {
		db_insertPage($site_id,$url); 		
 	}
 }
 
 function bl_updateBulkPageState($pages,$state_name,$state)
 {
	// Compte le nombre de page
 	$count = count($pages);
 	
 	// On modifie l'etat
 	db_updateBulkPageState($pages,$state_name,$state);
 	
 	// Si l'etat est supperieur à 2 on ignore le changement d'etat
 	if ($state>1) return;
 	
	// Si l'etat est égalle à zero c'est qu'on annule les changements'
 	if ($state==0) {
 		$count =$count*-1;
 	} 
 	db_incrementCounter($state_name,$count);
 }
 
 function bl_updatePage($page)
 {
 	try {
	 	db_Begin();
	 	db_updatePage($page);
	 	db_updatePageData($page);
	 	db_Commit();
 	} catch (Exception $e) {
 		db_Rollback();	
 	}
 }
 
 
?>
