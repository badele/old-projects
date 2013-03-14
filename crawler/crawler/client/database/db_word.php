<?php
/*
 * Created on 21 juin 08
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */
 
     function db_getWordByWord($word)
    {
		
		$result = db_query("select * from word where word='$word'");
		$row = mysql_fetch_assoc($result);
		mysql_free_result($result);
		
		return $row;
    }
 

    function db_addWord($word)
    {
    	$url = myaddslashes($word);
    	
    	db_query ("insert into word (word) values ('$word')");
    	
    	return mysql_insert_id();
    }


 	/*function db_isWordedExist($page_id,$word_id)
 	{
 		$result = db_query("select * from worded where page_id='$page_id' and word_id='$word_id'");
		$row = mysql_fetch_assoc($result);
		mysql_free_result($result);
		
		return $row;
		
	 }*/

    function db_createWorded($page_id,$word_id,$weight,$density)
    {
		$density = $density*-1;
		$weight = $weight*-1;
		
		// Bidouille à 3 francs si sous
    	$weight = str_replace(",",".",$weight);
    	$density = str_replace(",",".",$density);
    	
    	db_query ("insert into worded (page_id,word_id,weight,density) values ($page_id,$word_id,$weight,$density)");
    	
    	return mysql_insert_id();
    }
    
    
    function db_createFastWorded($page_id,$words)
    {
		$sql ="\nCREATE PROCEDURE `fastinsert`() BEGIN\n";
		foreach ($words as $word => $infos) { 
	    	$word = myaddslashes($word);
	
			$density= $infos['total']['avg_density'];
			$weight= $infos['total']['avg_weight'];

			$density = $density*-1;
			$weight = $weight*-1;
			
			// Bidouille à 3 francs si sous
	    	$weight = str_replace(",",".",$weight);
	    	$density = str_replace(",",".",$density);
	    	
	    	
	    	
//	    	db_query ("insert into worded (page_id,word_id,weight,density) values ($page_id,$word_id,$weight,$density)");
	    	$sql .= "insert into worded (page_id,word_id,weight,density) select $page_id,word_id,$weight,$density from word where word='$word';\n";
		}
		$sql .= "END";
    	
    	mysql_unbuffered_query('drop procedure if exists fastinsert');
    	mysql_unbuffered_query($sql);
    	mysql_unbuffered_query('call fastinsert()');
    }
    


 
    function db_insertWordedData($page_id,$word_id,$tag,$freq,$density,$weight)
    {
		// Contourne les index DESC non suporté pour l'instant
		$freq = $freq*-1;
		$density = $density*-1;
		$weight = $weight*-1;

		// Bidouille à 3 francs si sous
    	$density = str_replace(",",".",$density);

    	db_query ("update worded_data set $tag"."_freq=$freq,$tag"."_density=$density,$tag"."_weight=$weight where page_id=$page_id and word_id=$word_id");
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
?>
