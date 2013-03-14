<?php
/*
 * Created on 21 juin 08
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */
 

function bl_InsertWords($page_id,$words)
 {

    	foreach ($words as $word => $infos) 
    	{
			// On test si l'URL existe deja
			$worditem = db_getWordByWord($word);
			if (!$worditem) {
				$id = db_addWord($word);
			} else {
				// l'URL existe deja
				$id = $worditem['word_id'];
			}


    		//if (!db_isWordedExist($page_id,$id)) {
    			//db_createFastWorded($page_id,$id,$infos['total']['avg_weight'],$infos['total']['avg_density']);
    		//}
    		//db_insertWordedData($page_id,$id,$tag,$infos['freq'],$infos['density'],$infos['weight']);
    	}
    	db_createFastWorded($page_id,$words);
 }

?>
