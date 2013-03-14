<?php
/*
 * Created on 21 juin 08
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */
 
 class data_link 
 {
 	public $md5_url;
 	public $link;
 }
 
 class data_link_to
 {
 	public $from_md5_url;
 	public $to_md5_url;
 	public $url;
 }
 

    function db_getNextLinkScheluded($number_rows=1)
    {
		$result = db_query("select link_temp.* from link_temp  limit $number_rows for update");
		
		$rows = db_mysql_fetch_rows($result);
		mysql_free_result($result);

		return $rows;
    }
    
    function db_deleteBulkLinkState($links)
    {
		foreach($links as $row => $data) {
			$page_id = $data['page_id'];
			$md5_url = $data['md5_url'];
			
			db_query("delete from link_temp where page_id=$page_id and md5_url='$md5_url'");
		}
    }
    


     function db_getLinkByURL($url)
    {
    	$url = myaddslashes($url);
		
		$result = db_query("select * from link where link='$url'");
		$row = mysql_fetch_assoc($result);
		mysql_free_result($result);
		
		return $row;
    }
 

    function db_addlink($url)
    {
    	$url = myaddslashes($url);
    	
    	db_query ("insert into link (link) values ('$url')");
    	
    	return mysql_insert_id();
    }

    function db_countLinks()
    {
		$result = db_query("select sum(link_count) from page where link_count>0");
		$row = mysql_fetch_row($result);
		
		return $row[0];
    }


    function db_moveFromtemplinkfrom_Tolinkfrom()
    {
    	db_query ("call moveFromtemplinkfrom_Tolinkfrom()");
    }

    function db_moveFromtemplinkto_Tolinkto()
    {
    	db_query ("call moveFromtemplinkto_Tolinkto()");
    }

	

	function db_getNextLink()
	{
		$result = db_query("select link.*,site.site_id from site,link where locate(url,link.link)>0 and state_taskpage=0 limit 1");
		$row = mysql_fetch_assoc($result);
		mysql_free_result($result);
		
		return $row;
	}



    function db_addlinkto($page_id,$link_id,$count)
    {
    	db_query ("insert into link_to (page_id,link_id,count) values ($page_id,$link_id,$count)");
    }
 
 
 
    /*function db_addlinkto($page_id,$link,$count)
    {
    	$link = myaddslashes($link);

    	db_query ("insert into temp_link_to  (page_id,link,count) values ($page_id,'$link',$count)");
    }*/

//	function db_addlinks($page_id,$urls) 
//	{
//
//		$sql ="\nCREATE PROCEDURE `fastinsert`() BEGIN\n";
//    	foreach ($urls as $url =>$data) 
//    	{
//	    	$url = myaddslashes($url);
//			$freq = $data['freq'];
//			
////	    	db_query ("insert into worded (page_id,word_id,weight,density) values ($page_id,$word_id,$weight,$density)");
//	    	$sql .= "insert into temp_link_to  (page_id,link,count) values ($page_id,'$url',$freq);\n";
//		}
//		$sql .= "END<br><br>";
//
//		print $sql;
//    	
//    	mysql_unbuffered_query('drop procedure if exists fastinsert');
//    	mysql_unbuffered_query($sql);
//    	mysql_unbuffered_query('call fastinsert()');
//
//		
//	}


/*    function db_add_templinked($page_id,$link,$count)
    {
    	db_query ("insert into temp_link (page_id,link,count) values ($page_id,'$link',$count)");
    	return mysql_insert_id();
    }*/

    function db_addlinkfrom($page_id,$link_id,$word_id)
    {
	    	db_query("insert into link_from (from_page_id,link_id,word_id) values ($page_id,$link_id,$word_id)");
    }

    function db_addlinkfrom_test($page_id,$link_id,$word)
    {
	    	$word = myaddslashes($word);
	    	
	    	return "($link_id,'$word')";
    }



    function db_SP_MoveFromtemplinkToLink()
    {
    	db_query ("call moveFromtemplinkToLink()");
    	return mysql_affected_rows();
    }

    
    /*function db_updateLinkState($link_id,$state)
    {
    	db_query ("update link set state_taskpage=$state where link_id=$link_id");
    }*/

    
    /*function db_delLinks($page_id)
    {
    	db_query ("delete from linked where page_id=$page_id");
    }

	*/
	
    /*
     * ############# link_temp ###################
     */
    
    function db_InsertLinkTemp($md5_url,$url)
    {
    	$url = myaddslashes($url);
    	
    	$sql = sprintf("replace into link_temp (md5_url,link) values ('%s','%s')",$md5_url,$url);
    	db_query ($sql);
    	
    	return mysql_insert_id();
    }
    
    function db_GetLinkTemp($md5_url) {

		$sql = sprintf("select * from link_temp where md5_url='%s'", $md5_url);
		$result = db_query($sql);
		$rows = db_mysql_fetch_object($result,'data_link');
		$count = count($rows);
		mysql_free_result($result);
    }
    
    function db_GetNextLinkTemp() {
		$sql = sprintf("select * from link_temp limit 1");
		$result = db_query($sql);
		$rows = db_mysql_fetch_object($result,'data_link');
		$count = count($rows);
		mysql_free_result($result);
		
		return $rows;
    }
    
    function db_InsertLinkFrom($from_md5_url,$to_md5_url)
    {
    	$sql = sprintf("replace into link_from_temp (from_md5_url,to_md5_url) values ('%s','%s')",$from_md5_url,$to_md5_url);
    	db_query ($sql);
    	
    	return mysql_insert_id();
    }
	
	
?>
