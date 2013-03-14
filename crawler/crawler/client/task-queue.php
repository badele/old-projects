<?php
/*
 * Created on 13 juin 08
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */
 
 include 'conf.php';
 
 
 include '../commons/database.php';
 include '../commons/fonctions.php';
 include 'tasks.php';
 include 'queue.php';
 
 include "database/db_page.php";
 include "database/bl_page.php";

 include "database/db_link.php";
 include "database/bl_link.php";

 include "database/db_word.php";
 include "database/bl_word.php";

 include "database/db_site.php";
 


$all_links = array(); 
 
// Charge les infos du site

/*$site = getSite('http://www.jesuislibre.org/');
bl_InsertPage($site['site_id'],$site['url']);
db_updateAllPageState('crawled',0);*/

// Ajoute les pages des sites
function queue_crawl($queues,$taskid)	
{
	try {
		showInformation(".");
		crawlPage($queues,$taskid);
		$queues->Delete('queue',$taskid);
		
	} catch (Exception $e) {
		showError();
		showInformation($e->getMessage());
		return false;
	}
}

function pages_crawl($queues,$taskid)	
{
	try {
		showInformation(".");
		
		$item = $queues->Items();
		$page = $item[$taskid]['object'];

		bl_updatePage($page);
		$queues->Delete('pages',$taskid);
		
	} catch (Exception $e) {
		showError();
		showInformation($e->getMessage());
		return false;
	}
}

function pages_crawl_links($queues,$taskid)	
{
	try {
		showInformation(".");

		$item = $queues->Items();
		$object = $item[$taskid]['object'];
		
		$from_md5_url = $object['md5_url'];
		$links = $object['links'];

		bl_InserLinkFrom($from_md5_url,$links);
		$queues->Delete('pages',$taskid);

	} catch (Exception $e) {
		showError();
		showInformation($e->getMessage());
		return false;
	}
}

function links_links($queues,$taskid)	
{
	try {
		showInformation(".");


		$item = $queues->Items();
		$page_links = $item[$taskid]['object'];

		$GLOBALS['all_links'] = array_unique(array_merge($GLOBALS['all_links'],$page_links));
		$queues->Delete('links',$taskid);
	} catch (Exception $e) {
		showError();
		showInformation($e->getMessage());
		return false;
	}
}



db_insertPageFromSite();

RunTask();



?>
