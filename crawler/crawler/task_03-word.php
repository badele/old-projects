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




while (1) {
	db_disableIndex('word');
	db_disableIndex('worded');
	extractWordsAll();
	db_enableIndex('word');
	db_enableIndex('worded');
	
	showInformation("word wait<br>");
	sleep($GLOBALS['wait_process']);
}

?>
