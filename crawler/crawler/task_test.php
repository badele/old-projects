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
//db_updateAllPageState('linked',0);


function prepareSort() 
{
	$tags = arsort($GLOBALS['weight_intags']);

	$sort='';
	$i=0;
	foreach ($GLOBALS['weight_intags'] as $tagkey => $value) {
			if ($i>0) $sort .= ",";
			$sort .= "$tagkey"."_weight";
			//$sort .= ",$tagkey"."_density";
			$i++;
	}
	
	print $sort;
	
}

function updatePageInformation()
{
	$page = db_getNextPageScheluded('crawled');

	while ($page)
	{
		showStatistics();
		$page_id = $page['page_id'];
		$url = $page['url'];
		$site_id = $page['site_id'];
	
		$page = db_getPagebyID($page_id);
		$html = gzuncompress($page['html']);
		$size = strlen($html);
		if ($size<8000000) {
			$content = cleanDocument($url, $html);
			$data = getInfoHTMLPage($url, $content);
			
			
			$title = myaddslashes($data['title']);
			$md5 = myaddslashes($data['md5']);
			$text = myaddslashes($data['mybody']);


			db_query("update page set title='$title',md5='$md5',size=$size where page_id=$page_id");
			db_query("update page_data set text='$text' where page_id=$page_id");
			
		}
		if (!isError()) {
			db_updatePageState($page_id,'crawled',1);
		}
		$page = db_getNextPageScheluded('crawled');
	}
	
}

function updateWordToLink()
{
	$page = db_getNextPageScheluded('crawled');

	while ($page)
	{
		showStatistics();
		$page_id = $page['page_id'];
		$url = $page['url'];
		$site_id = $page['site_id'];
	
		$page = db_getPagebyID($page_id);
		$html = gzuncompress($page['html']);
		$size = strlen($html);
		if ($size<8000000) {
			$content = cleanDocument($url, $html);
			$data = getInfoHTMLPage($url, $content);
			
			
			$title = myaddslashes($data['title']);
			$md5 = myaddslashes($data['md5']);
			$text = myaddslashes($data['mybody']);


			db_query("update page set title='$title',md5='$md5',size=$size where page_id=$page_id");
			db_query("update page_data set text='$text' where page_id=$page_id");
			
		}
		if (!isError()) {
			db_updatePageState($page_id,'crawled',1);
		}
		$page = db_getNextPageScheluded('crawled');
	}
	
}


function prepareCalcWeight() {

	$tags = arsort($GLOBALS['weight_intags']);

	
	$sql_weight="weight=(";
	$sql_density="density=(";
	$i=0;
	foreach ($GLOBALS['weight_intags'] as $tagkey => $value) {
			$i++;
			if ($i>1) {
				$sql_weight .= "+";	
				$sql_density .= "+";	
			}
			$sql_weight .= $tagkey."_weight";
			$sql_density .= $tagkey."_density";
	}
	$sql_weight .= ")/".$i;
	$sql_density.= ")/".$i;
	print "update worded set $sql_weight,$sql_density";
}

//prepareSort();

function testURL()
{
	$url = "http://localhost.localdomain/wikipedia/fr/articles/l/i/c/Licence_publique_g%C3%A9n%C3%A9rale_limit%C3%A9e_GNU_735a.html";
	
	print convertToUTF(urldecode($url));	
}

//updatePageInformation();

function testSpeedDownload()
{
	//showElapsedTime('start');
	for ($i=0;$i<100;$i++) {
		downloadDocument("http://localhost.localdomain/wikipedia/fr/articles/l/e/_/Wikipédia~Le_Bistro_décembre_2005_b706.html");
	}
	//showElapsedTime('downloaded');
	
}

//testSpeedDownload();

    function db_getNext()
    {
		//print "select * from page,page_data where page.page_id=$id and  page.page_id=page_data.page_id;\n"; 
		db_Begin();
		$result = db_query("select * from page where state_crawled=0 for update");
		$row = mysql_fetch_assoc($result);
		mysql_free_result($result);
		
		$page_id = $row['page_id'];
		db_query("update page set state_crawled=2 where page_id=$page_id");
		db_Commit();
		
		return $row;
    }


function test_crawl()
{
	$page = db_getNext();
	while ($page) {
		showStatistics1();
		$page_id = $page['page_id'];
		db_Begin();
		db_query("update page set state_crawled=1 where page_id=$page_id");
		db_Commit();
		$page = db_getNext();
	}
}


function test_bulk_crawl()
{
	$pages = db_getNextPageScheluded('crawled',$GLOBALS['nb_bulk_lines']);

	while ($pages) {
			foreach ($pages as $item => $page)
			{
				showStatistics1();
				$page_id = $page['page_id'];
				db_Begin();
				db_query("update page set state_crawled=1 where page_id=$page_id");
				db_Commit();
			}
			$pages = db_getNextPageScheluded('crawled',$GLOBALS['nb_bulk_lines']);
	}
}

function test_bulk_crawl1()
{
db_query("update page set state_crawled=0;");
db_query("update counter set value=0;");

	$pages = db_getNextPageScheluded('crawled',$GLOBALS['nb_bulk_lines']);

	while ($pages) {
			db_Begin();
			foreach ($pages as $item => $page)
			{
				//showStatistics1();
				$page_id = $page['page_id'];
				sleep(0.05);
				db_query("update page set state_crawled=1 where page_id=$page_id");
			}
			db_incrementCounter('crawled',count($pages));
			db_Commit();
			$pages = db_getNextPageScheluded('crawled',$GLOBALS['nb_bulk_lines']);
	}
}


function test_parse()
{
	$result = array();
	
	$page_id = 999999;
	$md5_url = 'md5';
	$site_id = 999999;


	$url = 'http://localhost.localdomain/wikipedia/fr/articles/l/e/i/Leishmaniose.html';
	$data  = downloadDocument($url);

	$html = $data['html'];
	$date = date( 'Y-m-d H:i:s');
	$md5 = md5($html);
	$size = strlen($html);


	$link_count = -1;
	if (strlen($html)<=$GLOBALS['max_document_size']) {
		$links = extract_links1($url,$html);
		showElapsedTime("crawl extract_links: $url");	
		$link_count = count($links);
		bl_InsertLinks_new1($page_id,$links,$site_id,'http://localhost.localdomain/wikipedia/fr');
		showElapsedTime("crawl bl_InsertLinks_new1: $url");	
		//showElapsedTime('bl_InsertLinks_new db_updatePageState');
	}

}

function test_crawl1()
{
	
	db_query("update page set state_crawled=0;");
	db_query("update counter set value=0;");

	$pages = db_getNextPageScheluded('crawled',5000);

	try {
		foreach ($pages as $item => $page)
		{
			$page_id = $page['page_id'];
			$url = $page['url'];
			$md5_url = md5($page['url']);
	
			//showStatistics1();
			//showInformation("$page_id<br>");
			$data  = downloadDocument($url);
			db_replacePageContent($md5_url,$page_id,$data);		
			db_query("update page set state_crawled=1 where page_id=$page_id");
		}
	} catch (Exception $e) {
			showError();
			showInformation($e->getMessage());
			exit;
	}
	
}

showElapsedTime('crawl before');
test_bulk_crawl1();
showElapsedTime('crawl end');



?>
