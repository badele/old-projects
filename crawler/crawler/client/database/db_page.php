<?php
/*
 * Created on 21 juin 08
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */

class data_minimal_page 
{
	public $page_id;
	public $md5_url;
	public $url;
	public $site_id;
	
	function assignTo($dst)
	{
		$dst->page_id = $this->page_id;
		$dst->md5_url = $this->md5_url;
		$dst->url = $this->url;	
		$dst->site_id = $this->site_id;	
	}
}

class data_page 
{
	public $page_id;
	public $md5_url;
	public $url;
	public $site_id;
	
	public $date;
	public $title;
	public $html;
	public $text;
	public $header;
	public $http_code;
	public $md5;
	public $size;
	public $lastcrawl;
}


 
function db_searchPages($words,$page) 
{
	
	$words = split(" ",convertToUTF('UTF-8',$words));
 	$sql="";
 	$i=0;
 	foreach ($words as $word) {
 		$word = myaddslashes($word);
 		if ($i==0) {
 			$sql = "select page.* from word,worded,page " .
 					"where word='$word' " .
 					"and worded.word_id=word.word_id " .
 					"and worded.page_id=page.page_id";
 		} else {
			$sql .= " and worded.page_id in 
			(
			select page_id from word,worded where 
			word='$word'
			and worded.word_id=word.word_id
			)";
 			
 		}
 		$i++;
 	}
 	$sql .= "order by weight,count_backlink ";
 	$sql .= "limit ".(($page-1)*10).",10";
 	
 	$result = db_query($sql);
	while ($row = mysql_fetch_assoc($result)) {
		$rows[] = $row; 
	}
	mysql_free_result($result);
	
	return $rows;
}
 	
/*select page.* from word,worded,page where 
word='linux'
and worded.word_id=word.word_id
and worded.page_id=page.page_id
and worded.page_id in 
(
select page_id from word,worded where 
word='debian'
and worded.word_id=word.word_id
)
order by count_backlink,weight
*/
 	
	
	

function db_SP_bulkInserPage()
{
    	/*db_query ("insert into page (site_id,url) select site.site_id,link.link from site,link 
	left join page on link.link = page.url
	where locate(site.url,link.link)>0 and state_taskpage=0 and page.page_id is null");*/
	
	db_query("CALL insertPagesFromLinks()");
	return mysql_affected_rows(); 
}
 
    function db_insertPage($site_id,$url)
    {
/*    	$url = myaddslashes($url);
    	$content = myaddslashes($content);
    	$text = strip_tags($content);
    	$title = myaddslashes('title');
    	$md5 = myaddslashes(md5($content));
    	$size = strlen($content);
    	db_query ("replace into page (site_id,url,content,text,title,size,md5) values ($site_id,'$url','$content','$text','$title',$size,'$md5')");
    	*/
    	$url = myaddslashes($url);
    	db_query ("replace into page (site_id,url) values ($site_id,'$url')");
    }
    
    function db_replacePageContent($md5_url,$page_id,$content)
    {
    	$http_code = $content['http_code'];
    	$header = myaddslashes($content['header']);
    	$html = myaddslashes(gzcompress(trim($content['html']),9));
    	db_query ("replace into page_data (md5_url,page_id,html,http_code,header) values ('$md5_url',$page_id,'$html',$http_code,'$header')");
    }



/*    function db_updatePage($md5_url,$page_id,$content)
    {
    	$http_code = $content['http_code'];
    	$header = myaddslashes($content['header']);
    	$html = myaddslashes(gzcompress(trim($content['html']),9));
    	db_query ("replace into page_data (md5_url,page_id,html,http_code,header) values ('$md5_url',$page_id,'$html',$http_code,'$header')");
    }*/

	function db_updatePage(data_page $page)
	{
		$sql = sprintf("update page set lastcrawl='%s',size=%d,md5='%s',title='%s' where md5_url='%s'"
						, $page->date
						, $page->size
						, myaddslashes($page->md5)
						, myaddslashes($page->title)
						, myaddslashes($page->md5_url) 
		
		);
		db_query($sql);
	}

	function db_updatePageData(data_page $page)
	{
		$sql = sprintf("replace into page_data (md5_url,html,text,header,http_code) values ('%s','%s','%s','%s',%d)"
						, myaddslashes($page->md5)
						, myaddslashes($page->html)
						, myaddslashes($page->text)
						, myaddslashes($page->header)
						, $page->http_code
						); 
		
		db_query($sql);
	}



    

    function db_updatePageTitle($page_id,$title)
    {
    	$title = myaddslashes($title);
    	db_query ("update page set title='$title' where page_id=$page_id");
    }

/*    function db_updatePage($page_id,$date,$size,$md5,$title,$count)
    {
    	$title = myaddslashes($title);
    	db_query ("update page set lastcrawl='$date',size=$size,md5='$md5',title='$title',link_count=$count where page_id=$page_id");
    }*/

/*    function db_updatePage($md5_url,$date,$size,$md5,$title,$count)
    {
    	$title = myaddslashes($title);
    	db_query ("update page set lastcrawl='$date',size=$size,md5='$md5',title='$title',link_count=$count where md5_url='$md5_url'");
    }*/



    
    function db_updatePageState($page_id,$state_name,$state)
    {
    	//print "update page set state_$state_name=$state where page_id=$page_id;\n";
    	db_query ("update page set state_$state_name=$state where page_id=$page_id");
    }


    
    function db_updateBulkPageState($pages,$state_name,$state)
    {
    	$values = "";
		$i=0;
		
		foreach($pages as $row => $data) {
			if ($i>0) {$values .= ",";}
			
			$values .= $data->page_id;
			$i++;
		}
		
		db_query("update page set state_$state_name=$state where page_id in ($values)");
    }

    function db_updateAllPageState($state_name,$state)
    {
    	db_query ("update page set state_$state_name=$state");
    }

    
    function db_getPagebyURL($url)
    {
		$url = myaddslashes($url);
		
		$result = db_query("select * from page where url='$url'");
		$row = mysql_fetch_assoc($result);
		mysql_free_result($result);
		
		return $row;
    }
    
    function db_countPages()
    {
		return db_getincrementCounter('crawled');
    }
    



    function db_getPagebyID($id)
    {
		//print "select * from page,page_data where page.page_id=$id and  page.page_id=page_data.page_id;\n"; 
		$result = db_query("select * from page,page_data where page.page_id=$id and  page.page_id=page_data.page_id");
		$row = mysql_fetch_assoc($result);
		mysql_free_result($result);
		
		return $row;
    }


    
    function db_getNextPageScheluded($state_name,$number_rows=1)
    {
		db_Begin();

		$result = db_query("select page.* from page where state_$state_name=0  and site_id in (select site_id from site where disable=0) limit $number_rows for update");
		$rows = db_mysql_fetch_rows($result);
		$count = count($rows);
		mysql_free_result($result);
		if ($count>0) bl_updateBulkPageState($rows,$state_name,2);

		db_Commit();
		
		return $rows;
    }

	function db_getNextPageScheluded1($state_name,$number_rows=1)
    {
		db_Begin();

		$result = db_query("select page_id,site_id,md5_url,url from page where state_$state_name=0  and site_id in (select site_id from site where disable=0) limit $number_rows for update");
		$rows = db_mysql_fetch_object($result,'data_minimal_page');
		$count = count($rows);
		mysql_free_result($result);
		if ($count>0) bl_updateBulkPageState($rows,$state_name,2);

		db_Commit();
		
		return $rows;
    }
	

    function db_getNextScheludedAfterCrawled($state_name)
    {
		//mt_start();
		//print "select page.* from page where state_$state_name=0  and state_crawled=1 and site_id in (select site_id from site where disable=0) limit 1;\n"; 
		$result = db_query("select page.* from page where state_$state_name=0  and state_crawled=1 and site_id in (select site_id from site where disable=0) limit 1");
		$row = mysql_fetch_assoc($result);
		mysql_free_result($result);
		//print "db_getNextPageScheluded ".mt_end().'<br>';
		
		return $row;
    }

    
 
?>
