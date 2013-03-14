<?php
/*
 * Created on 13 juin 08
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */
 

// Recupere une pages web
function crawl($page)
{
	if ($page)
	{
		$page_id = $page['page_id'];
		$url = $page['url'];
		$md5_url = $page['md5_url'];
		$site_id = $page['site_id'];

		//showElapsedTime("time for $url");
		//noError();
		$data =  downloadDocument($url);
		showElapsedTime('after downloadDocument');
				
		if ($data) {
			$html = $data['html'];
			$date = date( 'Y-m-d H:i:s');
			$md5 = md5($html);
			$size = strlen($html);
			$site = db_getSitebyID($site_id);
			showElapsedTime('db_getSitebyID');
			
			//noError();
			//db_Begin();
			//showElapsedTime('db_Begin');
			db_replacePageContent($md5_url,$page_id,$data);
			showElapsedTime('db_replacePageContent');
			db_updateSiteCrawled($site_id,$date);
			showElapsedTime('db_updateSiteCrawled');
			db_incrementPageCount($site_id);
			showElapsedTime('db_incrementPageCount');
			db_updatePageState($page_id,'crawled',1);
			showElapsedTime('db_updatePageState');
			
			$link_count = -1;
			if (strlen($html)<=$GLOBALS['max_document_size']) {
				$links = extract_links1($url,$html);
				showElapsedTime("crawl extract_links: $url");	
				$link_count = count($links);
				bl_InsertLinks_new1($page_id,$links,$site_id,$site['url']);
				showElapsedTime("crawl bl_InsertLinks_new1: $url");	
				//showElapsedTime('bl_InsertLinks_new db_updatePageState');
			}
			
			//db_updatePageState($page_id,'linked',0);
			//showElapsedTime('linked db_updatePageState');
			//db_updatePage($page_id,$date,$size,$md5,'',$link_count);
			db_updatePage($md5_url,$date,$size,$md5,'',$link_count);
			showElapsedTime('db_updatePage');
			//db_addlinkCount($site_id,$link_count);			
			//db_query("call insertPagesFromLinks");

			//db_Commit();
			//showElapsedTime('db_Commit');
			//showInformation("<br>");
		}
	}
}


function crawlPage($queues,$taskid)
{
	$items = $queues->Items();
	$page_tmp = $items[$taskid]['object'];
	
	$data = downloadDocument($page_tmp->url);
	showElapsedTime('after downloadDocument');
			
	if ($data) {
		$title = $data['title'];
		$html = $data['html'];
		$header = $data['header'];
		$http_code = $data['http_code'];
		
		$md5 = md5($html);
		$size = strlen($html);
		$site = db_getSitebyID($page_tmp->site_id);
		
		$page = new data_page();
		$page_tmp->assignTo($page);
		$page->date = date( 'Y-m-d H:i:s');
		$page->html = $html;
		$page->md5 = $md5;
		$page->title = $title; 
		
		$queues->Save('pages','crawl'.$page->md5_url,$page);
		
		if (strlen($html)<=$GLOBALS['max_document_size']) {
			$links = extract_links1($page->url,$html);
			showElapsedTime("crawl extract_links: $page->url");	
			
	   		// Ajoute les valeurs SQL des liens
			
			/*$sql_link = "";
	    	foreach ($links as $url =>$data) 
	    	{
	    		$md5_url = md5($url);
	    		$sql_link .= sprintf("('%s','%s')\n",$md5_url,myaddslashes($url));
	    	}*/
			//q_saveGlobalResult('links',$sql_link,false);
			
			
			$queues->Save('links','links'.$page->md5_url,array_unique(array_keys($links)));
			
			$link_data = array("page_id" => $page->page_id,"md5_url" => $page->md5_url,"links" => $links,"site" => $page->site_id,"site_url" => $site['url']); 
			$queues->Save('pages','crawl_links'.$page->md5_url,$link_data);
			
			showElapsedTime("crawl bl_InsertLinks_new1: $page->url");	
			//showElapsedTime('bl_InsertLinks_new db_updatePageState');
		}
		
		showElapsedTime('db_updatePage');
	}
}



// met à jours les donnée de la page
function extractData()
{
	$page = db_getNextPageScheluded('updated');
	
	if ($page)
	{
		$page_id = $page['page_id'];
		$url = $page['url'];
	
		noError();
		showInformation("update $url<br>");
		$data = db_getPagebyID($page_id);
		$html = @gzuncompress($data['html']);
		
		var_dump($html);exit;
		if (!isError()) {
			$metadata = @getMetadata($url,gzuncompress($html));
			$title = $metadata['title'];
			if (!isError()) {
				db_updatePageTitle($page_id,$title);	
				db_updatePageState($page_id,'updated',1);
			} 
		}
	}
}



 

// Extrait les urls d'une page'
function extractLinks()
{
	//mt_start();
	$page = db_getNextScheludedAfterCrawled('linked');
	if ($page)
	{
		
		$page = db_getPagebyID($page['page_id']);
		$page_id = $page['page_id'];
		$url = $page['url'];

		// Indique que l'on travaille sur cet enregistrement
		//db_updatePageState($page_id,'linked',3);

		$html = gzuncompress($page['html']);
		noError();
		if (strlen($html)<=$GLOBALS['max_document_size']) {
			//showInformation("extract Link from $url<br>");
			$links = extract_links($url,$html);
	
			bl_InsertLinks($page_id,$links);
		}
		showError();
		if (!isError()) {
			db_updatePageState($page_id,'linked',1);
		} else {
			db_updatePageState($page_id,'linked',-1);
		}
	}
	//print "extractLinks ".mt_end().'<br>';
}

// Extrait les mots d'une page'
function extractWords()
{
	$page = db_getNextScheludedAfterCrawled('keyword');
	if ($page)
	{
		$page = db_getPagebyID($page['page_id']);
		$page_id = $page['page_id'];
		$url = $page['url'];
		$html = gzuncompress($page['html']);
	
		noError();
		//showInformation("word insert from $url<br>");
		if (strlen($html)<8000000) {
	
			$content = cleanDocument($url, $html);
			$data = getInfoHTMLPage($url, $content);
			
			bl_InsertWords($page_id,$data["words"]);

		if (!isError()) {
			db_updatePageState($page_id,'keyword',1);
		}

		} else {
			print "plus grand que 8000000";
			db_updatePageState($page_id,'keyword',3);
			
		}

		
	}
}


// Ajoute de nouvelle page à indexer
/*function addTaskPage()
{
	// Cherche les urls à ajouter en tant que page
	$link = db_getNextLink();

	if ($link)
	{
		$link_id = $link['link_id'];
		$url = $link['link'];
		$site_id = $link['site_id'];

		noError();
		showInformation("taskpage $url<br>");

		bl_InsertPage($site_id,$url);
		
		if (!isError()) {
			db_updateLinkState($link_id,1);
		}
	}
}*/

// Recupere les pages webs
function crawlAll()
{
	$pages = db_getNextPageScheluded('crawled',$GLOBALS['nb_bulk_lines']);

	while ($pages) {
		db_Begin();
		try {
			foreach ($pages as $item => $page)
			{
				ShowStatistics1();
				crawl($page);
				
				$page_id = $page['page_id'];
			}
			bl_updateBulkPageState($pages,'crawled',1);
			db_Commit();
		} catch (Exception $e) {
			file_put_contents("/tmp/last_error.txt",$e->getMessage());
			db_Rollback();
			bl_updateBulkPageState($pages,'crawled',3);
			db_Close();
			//db_updatePageState($page_id,'linked',3);
			showError();
			showInformation($e->getMessage());
			exit;
		}
		
		$pages = db_getNextPageScheluded('crawled',$GLOBALS['nb_bulk_lines']);
		//ShowStatistics();
	}
}


function crawlAll1()
{
	
	showElapsedTime("queue Start");

	q_resetPageQueue();
	
	showElapsedTime("queue q_resetPageQueue");

	// On verifie si il y'a pas des pages à traiter dans la queue
	$pages = q_getPagesFromQueue();
	
	// Si il y'a rien on récupere les pages depuis la DB
	if (count($pages)==0) {
		$pages = db_getNextPageScheluded1('crawled',$GLOBALS['nb_bulk_page']);
		q_addToQueue('crawl',$pages);
	}

	// On traite la queue
	while ($pages) {
		
		try {
			foreach ($pages as $item => $page)
			{
				//ShowStatistics1();
				showInformation(".");
				crawl1($page);
			}
		} catch (Exception $e) {
			showError();
			showInformation($e->getMessage());
			exit;
		}
		showInformation("");
		showElapsedTime("queue end");
		
		exit;
		$pages = db_getNextPageScheluded('crawled',$GLOBALS['nb_bulk_lines']);
		//ShowStatistics();
	}
	exit;
}

function RunTask()
{
	$queues = new Queues();
	
	showElapsedTime("queue Start");

	$queues->Reset('queue');
	$queues->Reset('pages');
	$queues->Reset('links');
	
	
	showElapsedTime("queue q_resetPageQueue");

	// On verifie si il y'a pas des pages à traiter dans la queue
	$queues->Load('queue');
	
	// Si il y'a rien on recupere une nouvelle queue
	$pages = array();
	if (count($queues->Items())==0) {
		$pages = db_getNextPageScheluded1('crawled',$GLOBALS['nb_bulk_page']);
		
		foreach($pages as $item => $object) {
			$queues->Add('crawl',$object->md5_url,$object);	
		}
		$queues->SaveAll('queue');
	}

	// Crawle l'ensemble des pages de la queue
	$queues->ExecuteQueues('queue');

	// Insere les liens de chaque pages de la queue
	$queues->Load('links');
	$queues->ExecuteQueues('links');
	bl_BulkInsertLinksTemp($GLOBALS['all_links']);
	
	$queues->Load('pages');
	$queues->ExecuteQueues('pages');
}



function updatePageAll()
{
	$page = db_getNextPageScheluded('updated');
	
	while ($page)
	{
		updatePage();
		$page = db_getNextPageScheluded('updated');
	}
}


function parseAll()
{
	$link = db_getNextLink();

	while ($link)
	{
		parse();		
		$link = db_getNextLink();
	}
}

function extractLinksAll()
{
	$pages = db_getNextScheludedAfterCrawled('linked');

	while ($pages)
	{
		ShowStatistics();
		extractLinks();
		if (($GLOBALS['stat_counter']%$GLOBALS['nb_iteration'])==0) {
			//showInformation("bl_bulkUpdateLinks<br>");
			//bl_bulkUpdateLinks();
			//exit;
		}		
		$pages = db_getNextScheludedAfterCrawled('linked');
	}
	//exit;
	
}

function linkAll()
{
	$links = db_getNextLinkScheluded($GLOBALS['nb_bulk_lines']);

	$i_link = 0;
	$i_page = 0;
	$sql_link ="";
	$sql_page ="";
	while ($links) {
		foreach ($links as $item => $link)
		{
			ShowStatistics1();
    		$url = $link['link'];
    		$md5_url = md5($url);
    		$url_site = $link['url_site'];
    		$site_id = $link['site_id'];

			// Insere les liens
    		$i_link++;
    		if ($i_link>1) { $sql_link .= ","; }
    		$sql_link .= sprintf("('%s','%s',0)",$md5_url,myaddslashes($url));
    		
			if (strpos($url,$url_site)!==FALSE) {
	    		$i_page++;
	    		if ($i_page>1) { $sql_page .= ","; }
	    		$sql_page .= sprintf("(getincrement('page'),'%s','%s',%d)",md5($url),myaddslashes($url),$site_id);
			} 		
    		
		}

    	if ($sql_link!='') db_query("insert into link (md5_url,link,backlink_count)  values $sql_link on duplicate key update backlink_count=backlink_count+1;\n");
		if ($sql_page!='') db_query("insert into page (page_id,md5_url,url,site_id)  values $sql_page on duplicate key update test_count=test_count+1;\n");
		//print "insert into page (md5_url,url,site_id)  values $sql_page on duplicate key update test_count=test_count+1;\n";exit;

		db_deleteBulkLinkState($links);
		$links = db_getNextLinkScheluded($GLOBALS['nb_bulk_lines']);
	}
	
}



function extractWordsAll()
{
	$page = db_getNextScheludedAfterCrawled('keyword');

	while ($page)
	{
		ShowStatistics();
		extractWords();		
		$page = db_getNextScheludedAfterCrawled('keyword');
	}
	
}


/*function addTaskPageALl()
{
	$link = db_getNextLink();

	while ($link)
	{
		addTaskPage();		
		$link = db_getNextLink();
	}
}*/ 

function addTaskPageALl()
{
	return db_SP_bulkInserPage();
} 

 
 ?>
