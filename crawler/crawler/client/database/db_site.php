<?php
/*
 * Created on 21 juin 08
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */
 
    function db_getSitebyID($id)
    {
		$result = db_query("select * from site where site_id=$id");
		$row = mysql_fetch_assoc($result);
		mysql_free_result($result);
		
		return $row;
    }
 
 
/*    function db_insertPageFromSite()
    {
    	db_query ("insert into page (page_id,url,site_id,md5_url) select getIncrement('page'),site.url,site.site_id,md5(site.url) from site left join page on site.url=page.url where page.url is null and disable=0");
    }*/
    
    function db_insertPageFromSite()
    {
    	//db_query ("insert into page_data (md5_url) select md5(site.url) from site left join page on site.url=page.url where page.url is null and disable=0");
    	db_query ("insert into page (page_id,url,site_id,md5_url) select getincrement('page'),site.url,site.site_id,md5(site.url) from site left join page on site.url=page.url where page.url is null and disable=0");
    }
    
    
    function db_updateSiteCrawled($site_id,$date)
    {
    	db_query ("update site set last_crawled='$date' where site_id=$site_id");
    }
    
    function db_incrementPageCount($site_id)
    {
    	db_query ("update site set page_count=page_count+1  where site_id=$site_id");
    }

    function db_addlinkCount($site_id,$count)
    {
    	db_query ("update site set link_count=link_count+$count  where site_id=$site_id");
    }

    
 
?>
