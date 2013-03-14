<?php
/*
 * Created on 21 juin 08
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */
 
 

function bl_InsertLinks($page_id,$urls)
 {
    	$uniq_word = array();
    	$uniq_link = array();
		
		$temp_link_id = 0;
		$i_link = 0;
		$i_word = 0;
		$i_from = 0;
		$word_count = 0;
		$sql_link="";
		$sql_word="";
		$sql_from="";

		
		// Calcule la liste des mots unique
    	foreach ($urls as $url =>$data) 
    	{
    		// Calcule les mots
    		foreach ($data['words'] as $word => $temp_word_id) { 
				// Ajout les mots
	    		if (!isset($uniq_word[$word])) {
		    		$uniq_word[$word] = $temp_word_id;
    			}
    		}
    	}
		
		// Ajoute les valeurs SQL des mots
		foreach ($uniq_word as $word => $temp_word_id) { 
    		
    		$i_word++;
    		if ($i_word>1) { $sql_word .= ","; }
    		$sql_word .= sprintf("(%d,'%s')",$uniq_word[$word],myaddslashes($word));
		}
		


   		// Ajoute les valeurs SQL des liens
    	foreach ($urls as $url =>$data) 
    	{
    		$i_link++;
    		if ($i_link>1) { $sql_link .= ","; }
    		
    		$temp_link_id = $data['temp_id'];
    		$sql_link .= sprintf("(%d,'%s')",$temp_link_id,myaddslashes($url));
			    		
			// Ajout les jointures mot-> lien
			$word_count = 0;
			foreach ($data['words'] as $word => $info) 
			{
				$count = count($data['words']);
				if ($count>0) {
		    		$i_from++;
		    		if ($i_from>1) { $sql_from .= ","; }
		    		$sql_from .= sprintf("(%d,%d)", $temp_link_id,$uniq_word[$word]);
		    		$word_count = $word_count + $count;
				}
			}
			$GLOBALS['words_count'] = $GLOBALS['words_count'] + $word_count; 
    	}

		$GLOBALS['links_count'] = $GLOBALS['links_count'] + count($urls); 
		
		$sql ="";
				//$sql ="\ndelimiter //\n";
		$sql ="\nCREATE PROCEDURE `fastinsert`()\nBEGIN\n";
		//$sql .= "set profiling=1;";
		$sql .= "truncate temp_link_from_link;\n";
		$sql .= "truncate temp_link_from_word;\n";
		$sql .= "truncate temp_link_from;\n";
		if ($sql_link!='') $sql .= "insert into temp_link_from_link (temp_link_id,link) values $sql_link;\n";
		//if ($sql_word!='' ) $sql .= "insert into temp_link_from_word (temp_word_id,word) values $sql_word;\n";
    	//if ($sql_from!='' ) $sql .= "insert into temp_link_from (temp_link_id,temp_word_id) values $sql_from;\n";
		$sql .= "insert into link (link) select   temp_link_from_link.link from temp_link_from_link  left join link on temp_link_from_link.link=link.link where link.link is null;\n";
    	//$sql .=	"insert into word (word) select temp_link_from_word.word from temp_link_from_word  left join word on temp_link_from_word.word=word.word where word.word is null;\n";
		//$sql .= "delete from link_from where from_page_id=$page_id;\n";
		//$sql .= "delete from link_to where page_id=$page_id;\n";
		//$sql .= " insert into link_from (from_page_id,link_id,word_id)  select $page_id,link_id,word_id from temp_link_from inner join temp_link_from_link on temp_link_from.temp_link_id=temp_link_from_link.temp_link_id inner join link on temp_link_from_link.link = link.link inner join temp_link_from_word on  temp_link_from.temp_word_id=temp_link_from_word.temp_word_id inner join word on temp_link_from_word.word = word.word;\n";
		//$sql .= " insert into link_to (page_id,link_id) select $page_id,link_id from temp_link_from_link inner join link on temp_link_from_link.link=link.link;\n" ;
		
		/*$sql .= "
show profiles;

show profile for query 11;

		\n";*/
		$sql .= "END;\n"; 


    	/*print "drop procedure if exists fastinsert;\n";
    	print $sql;
    	print "call fastinsert();\n";
   		db_updatePageState($page_id,'linked',0);
    	exit;*/

		//file_put_contents("/tmp/sql/sql_$page_id.sql",$sql);
    	db_query('drop procedure if exists fastinsert');
    	db_query($sql);
    	db_query('call fastinsert()');
    	

   		//print "<br>Count : $word_count<br><br>";
    	
		//db_SP_MoveFromtemplinkToLink();
		
 }

function bl_InsertLinks_new($page_id,$urls,$site_id,$url_site)
 {
    	$uniq_word = array();
    	$uniq_link = array();
		
		$temp_link_id = 0;
		$i_link = 0;
		$i_word = 0;
		$i_from = 0;
		$word_count = 0;
		$sql_link="";
		$sql_word="";
		$sql_from="";

		
		/*// Calcule la liste des mots unique
    	foreach ($urls as $url =>$data) 
    	{
    		// Calcule les mots
    		foreach ($data['words'] as $word => $temp_word_id) { 
				// Ajout les mots
	    		if (!isset($uniq_word[$word])) {
		    		$uniq_word[$word] = $temp_word_id;
    			}
    		}
    	}
		
		// Ajoute les valeurs SQL des mots
		foreach ($uniq_word as $word => $temp_word_id) { 
    		
    		$i_word++;
    		if ($i_word>1) { $sql_word .= ","; }
    		$sql_word .= sprintf("(%d,'%s')",$uniq_word[$word],myaddslashes($word));
		}
		*/


   		// Ajoute les valeurs SQL des liens
    	foreach ($urls as $url =>$data) 
    	{
    		$i_link++;
    		
    		$temp_link_id = $data['temp_id'];
    		$sql_link .= sprintf("insert into link (link_id,md5_url,link,backlink_count)  values (getIncrement('link'),'%s','%s',0) on duplicate key update backlink_count=backlink_count+1;\n",md5($url),myaddslashes($url));
			
			if (strpos($url,$url_site)!==FALSE) {
	    		$sql_link .= sprintf("insert into page (page_id,md5_url,url,site_id)  values (getIncrement('page'),'%s','%s',%d) on duplicate key update test_count=test_count+1;\n",md5($url),myaddslashes($url),$site_id);
				//print "<b>($site_id-$url_site)$url</b><br>";
			}  else {
				//print "($site_id-$url_site)$url<br>";
			} 		
    	}

		$GLOBALS['links_count'] = $GLOBALS['links_count'] + count($urls); 
		
		$sql ="";
				//$sql ="\ndelimiter //\n";
		$sql ="\nCREATE PROCEDURE `fastinsert_$page_id`()\nBEGIN\n";
		if ($sql_link!='') $sql .= "$sql_link";
		$sql .= "END;\n"; 


    	/*print "drop procedure if exists fastinsert;\n";
    	print $sql;
    	print "call fastinsert();\n";
   		db_updatePageState($page_id,'linked',0);
    	exit;*/

		//file_put_contents("/tmp/sql/sql_$page_id.sql",$sql);
    	db_query($sql);
    	db_query("call fastinsert_$page_id()");
    	db_query("drop procedure if exists fastinsert_$page_id");
    	

   		//print "<br>Count : $word_count<br><br>";
    	
		//db_SP_MoveFromtemplinkToLink();
 }



 
 function bl_addtemp_linkfrom($page_id,$link_id,$words) 
{
    	$i=0;
    	$sql ="";
    	foreach ($words as $word => $value) 
    	{
			$GLOBALS['words_count'] = $GLOBALS['words_count'] + 1; 

			/*// On test si le mot existe deja
			$worditem = db_getWordByWord($word);
			if (!$worditem) {
				$word_id = db_addWord($word);
			} else {
				// l'URL existe deja
				$word_id = $worditem['word_id'];
			}*/
			
//			db_addlinkfrom($page_id,$link_id,$word_id);
			
    		$i++;
    		if ($i>1) { $sql .= ","; }
			$sql .= "($link_id,$value)";
    	}
    	
    	return $sql;
} 

function bl_bulkUpdateLinks()
{
	db_moveFromtemplinkfrom_Tolinkfrom();
	db_moveFromtemplinkto_Tolinkto();
}
 /*
 function InsertLinks($links)
 {
		$link = db_getLinkByURL($url);
    	foreach ($links as $url =>$count) {
    		db_addlink($page_id,$url,$count);
    	}
 }
 */
 
 function bl_BulkInsertLinksTemp($links)
 {
 	foreach ($links as $link) {
 		$md5url = md5($link);
 		db_InsertLinkTemp($md5url,$link);
 	}
 }
 
 function bl_GetNextLinkTemp()
 {
 	return db_GetNextLinkTemp();
 }
 
 function bl_InserLinkFrom($from_md5_url,$links)
 {
 	foreach ($links as $link => $link_info) {
 		$to_md5_url = md5($link);
 		db_InsertLinkFrom($from_md5_url,$to_md5_url);
 	}
 }
 
?>
