<?php

/*
 * Created on 13 juin 08
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */

//$stat_counter = 0;

ignore_user_abort(TRUE);

$latest_time = -1;

$links_count = 0;
$words_count = 0;
$mem_pages_count = 0;
$mem_links_count = 0;
$mem_words_count = 0;
$elapsedtime=mt_end();


function myaddslashes($string) {
	if (get_magic_quotes_gpc())
		return $string;

	return addslashes($string);
}

function mystripslashes($string) {
	if (get_magic_quotes_gpc())
		return $string;

	return stripslashes($string);
}

function showElapsedTime($message)
{
	$find = FALSE;

	if ($GLOBALS['show_elapsed_message']=='' || strpos($message,$GLOBALS['show_elapsed_message'])!==FALSE) {
		$end = mt_end();
		$elapsed = round($end - $GLOBALS['elapsedtime'], 4);
		if ($elapsed>$GLOBALS['show_elapsed_after']) {
				showInformation("$message: ".$elapsed.'<br>');
				$find = TRUE;
			
		}
		$GLOBALS['elapsedtime'] = mt_end();
	}
	
	return $find;
}

/*function showStatistics()
{
	showInformation("|");
	if (($GLOBALS['stat_counter']%$GLOBALS['nb_iteration'])==0) {
		$end = mt_end();
		$start = mt_start();

		$page_count = db_countPages();
		$link_count = db_countLinks();
		
		if ($end<1000000000) {
	
			$nbpages = $page_count-$GLOBALS['mem_pages_count'];
			$nblinks = $link_count-$GLOBALS['mem_links_count'];

			$GLOBALS['mem_pages_count'] = $page_count;
			$GLOBALS['mem_links_count'] = $link_count;


			$nbpages_sec = $nbpages/$end;
			$nblinks_sec = $nblinks/$end;
			
			$value = $GLOBALS['nb_iteration'] / $end;
	
			print "<br>";
			printf ("%d iteration in %.1f s, ",$GLOBALS['nb_iteration'],$end);
			printf ("%d pages (%.1f p/s), ",$nbpages,$nbpages_sec);
			printf ("%d links (%.1f l/s)",$nblinks,$nblinks_sec); 
//			if ($word_count>0) printf (" %d words in %.1f s (%.1f w/s)",$word_count,mt_end(),$word_second); 
			print "<br>";
			showInformation(" ");
		}
	}

	$GLOBALS['stat_counter'] = $GLOBALS['stat_counter'] + 1;
}
*/

function showProgress()
{
	showInformation("|");
}


function showStatistics1()
{
		showInformation("|");
		
		if (connection_aborted()==1) throw new Exception("Client aborded");
		

		if ($GLOBALS['latest_time']==-1) {
			$GLOBALS['latest_time']=mt_get();
			$end = mt_end();
			$start = mt_start();
		}
		

		
		/*print "end: ".mt_get()."<br>";
		print "last: ".($GLOBALS['latest_time']+5);
		print "<br><br>";*/
		
		if (mt_get()>$GLOBALS['latest_time']+$GLOBALS['stat_interval']) {
	
			$GLOBALS['latest_time']=mt_get();
			$end = mt_end();
			$start = mt_start();

			$page_count = db_countPages();
			$link_count = db_countLinks();

			
			$nbpages = $page_count-$GLOBALS['mem_pages_count'];
			$nblinks = $link_count-$GLOBALS['mem_links_count'];

			$GLOBALS['mem_pages_count'] = $page_count;
			$GLOBALS['mem_links_count'] = $link_count;


			$nbpages_sec = $nbpages/$end;
			$nblinks_sec = $nblinks/$end;
			
			//$value = $GLOBALS['nb_iteration'] / $end;
	
			print "<br>";
			printf ("%.1f s elapsed, ",$end);
			printf ("%d pages (%.1f p/s), ",$nbpages,$nbpages_sec);
			printf ("%d links (%.1f l/s)",$nblinks,$nblinks_sec); 
//			if ($word_count>0) printf (" %d words in %.1f s (%.1f w/s)",$word_count,mt_end(),$word_second); 
			print "<br>";
			showInformation(" ");
		}
}


//Encode une partie de l'URL, par exemple les espace devienne +
function encodeQuery($url) {

	$data = parse_url($url);
	if (!isset ($data['query']))
		return $url;

	$path = $data['path'];
	return $data['scheme'] . '://' . $data['host'] . $data['path'] . '?' . urlencode($data['query']);
}

// source http://snippets.dzone.com/posts/show/187
function canonical_path($path) {
	$canonical = preg_replace('|/\.?(?=/)|', '', $path);
	while (($collapsed = preg_replace('|/[^/]+/\.\./|', '/', $canonical, 1)) !== $canonical) {
		$canonical = $collapsed;
	}
	$canonical = preg_replace('|^/\.\./|', '/', $canonical);
	return $canonical;
}

// Transforme une URL potentielement relative en absolue
function absoluteURL($src_url, $url) {

	$base = urlWithoutFile($src_url);

	$url_info = parse_url(trim($url));
	// Url Relative
	if (!isset ($url_info['host'])) {
		if (strpos($url,'#')!==FALSE AND strpos($url,'#')==0  ) {
			// URL relative commencant par un anchor
			//$url = $src_url.$url;
			$url = $src_url;
		} else {
			// Url Relative
			$url = $base . $url;
		}
	}
	$result = canonical_path($url);

	//bricolo, contourne le bug de canonical_path
	$result = str_ireplace('http:/', 'http://', $result);
	$result = str_ireplace('https:/', 'https://', $result);
	return $result;
}

// Recupere le contenu du page web
function downloadDocument($url) {
	$doc = array ();

	$c = curl_init(encodeQuery($url));
	curl_setopt($c, CURLOPT_TIMEOUT, 60);
	curl_setopt($c, CURLOPT_CONNECTTIMEOUT, 20);
	curl_setopt($c, CURLOPT_RETURNTRANSFER, TRUE);
	curl_setopt($c, CURLOPT_HEADER, TRUE);

	$data = curl_exec($c);
	
	//$sAverageSpeedDownload = curl_getInfo( $c, CURLINFO_SPEED_DOWNLOAD )/1024;
	//print "average download $sAverageSpeedDownload";

	if ($data) {
		// Http code
		$doc['http_code'] = curl_getinfo($c, CURLINFO_HTTP_CODE);

		// Header
		$doc['header'] = "";
		if (preg_match('/([A-Za-z0-9]+:.*)\r\n\r\n/sm', $data, $match)) {
			$doc['header'] = $match[1];
		}

		// Html code
		$doc['html'] = "";
		if (preg_match('/\r\n\r\n(.*)/sm', $data, $match)) {
			$doc['html'] = $match[1];
		}

		// Title
		$doc['title'] = "";
		if (preg_match("#<title>(.*?)<\/title>#si", $doc['html'], $match)) {
			$doc['title'] = trim($match[1]);
		}
	}

	curl_close($c);

	return $doc;
}

// Epure le document HTML (suppression du style, javascript, etc ..)
function cleanDocument($url, $content) {
	$url_info = parse_url($url);
	$host = $url_info['host'];
	$path = '';
	if (isset ($url_info['path'])) {
		$path = $url_info['path'];
	}

	// Supprime les donnees inutile 
	$content = preg_replace("#<!--.*?-->#si", "", $content);
	$content = preg_replace("#<script.*?>.*?</script>#si", "", $content);
	$content = preg_replace("#<style.*?>.*?</style>#si", "", $content);

	return $content;
}
function getOnlyTagContent($tag, $content) {
	$result = '';

	if (preg_match_all("#< *$tag.*?>(.*?)< */ *$tag.*?>#si", $content, $match)) {
		$result = $match[1];
	}
	// Retourne l'ensemble des mots clef dans des $tag
	$result = implode(" ", $match[1]);
	return $result;
}

function wordsWeightToArray($words,$tag,$text) {
	$tmp_words = array();
	$weight = $GLOBALS['weight_intags'][$tag];
	
	$text = strtolower($text);
	$text = preg_replace("/[^_[:alnum:]]+/i", " ", $text);
	
	$allwords = split(" ",$text);

	// Ajoute les mots et compte le nombre d'apparition
	foreach ($allwords as $word) {
		if (strlen($word)>=$GLOBALS['minimal_word_size']) {
			// Compte le nombre de mot
			if (isset($tmp_words[$word]['freq'])) {
				$tmp_words[$word]['freq'] += 1;
			} else {
				$tmp_words[$word]['freq'] = 1;
			}
		}
	}


	// Calcule la densité et le poid
	$count = count($tmp_words);
	foreach ($tmp_words as $key => $value) {
		$words[$key][$tag]['density'] = $tmp_words[$key]['freq'] / $count * 100;
		$words[$key][$tag]['weight'] = $tmp_words[$key]['freq'] * $weight;
	}
	
	return $words;
}

function wordsToArray($text) {
	$words = array();
	$tmp_words = array();
	
	$text = strtolower($text);
	$text = preg_replace("/[^[:alnum:]]+/i", " ", $text);
	
	$allwords = split(" ",$text);

	// Ajoute les mots et compte le nombre d'apparition
	foreach ($allwords as $word) {
		if (strlen($word)>=$GLOBALS['minimal_word_size']) {
			// Compte le nombre de mot
			if (!isset($words[$word])) {
				$GLOBALS['autoincrement'] = $GLOBALS['autoincrement'] + 1; 
				$words[$word] = $GLOBALS['autoincrement'];
			}
		}
	}
	return $words;
}


/*function calcTotalWeight($data)
{
	$words = array();	

	foreach ($GLOBALS['weight_intags'] as $tagkey => $value) {
			var_dump($data["$tagkey"."_words"]);
			foreach ($data["$tagkey"."_words"] as $word => $value) {
				print "$word => ".$value['weight']." <br>";
				
			}
	}
}*/

function removeTagContent($tag, $content) {
	$result = '';
	$content = preg_replace("#< *$tag.*?>(.*?)< */ *$tag.*?>#si", '', $content);

	return $content;
}

// Converti le texte en UTF-8 et sans accent
// Source http://fr3.php.net/manual/fr/function.iconv.php
function convertToUTF($charset, $s) {
	setlocale(LC_ALL, 'fr_FR.UTF8');

	noError();
	$r = '';
	$s1 = iconv($charset, 'ASCII//TRANSLIT', $s);
	if (isError()) return $s;
	
	for ($i = 0; $i < strlen($s1); $i++) {
		$ch1 = $s1[$i];
		$ch2 = mb_substr($s, $i, 1);

		$r .= $ch1 == '?' ? $ch2 : $ch1;
	}
	return $r;
}


// Récupere quelques information concernant la page
function getInfoHTMLPage($url, $content) {

	$uniquewords = array();
	$metadata = array ();
	$html_head = "";

	$metadata['scheme'] = '';
	$metadata['host'] = '';
	$metadata['path'] = '';
	$metadata['query'] = '';
	$metadata['title'] = '';
	$metadata['keywords'] = '';
	$metadata['description'] = '';
	$metadata['base'] = '';
	$metadata['robot'] = '';


	$metadata['md5'] = $md5 = md5($content);

	// HTML Head
	if (preg_match('#<head>(.*?)</head>#si', $content, $match)) {
		$result = trim($match[1]);
		$html_head = $result;
	}
	

	// Titre (avant encodage)
	if (preg_match('#<title>(.*?)</title>#si', $html_head, $match)) {
		$result = trim($match[1]);
		$metadata['title'] = $result;
	}
	
	// Cherche le charset
	if (preg_match('#<meta http-equiv=.*? charset=[\"\']?(.*?)[\"\']? .*>#si',$html_head,$match)) {
		$metadata['charset'] = trim(strtolower($match[1]));		
	} else {
		$metadata['charset'] = 'iso-8859-1';
	}


	// Essais de convertir le texte en UTF et sans accent
	//if ($metadata['charset']!='utf-8') {
		$content = convertToUTF($metadata['charset'],$content);
	//}
	
	// Recupere les infos de l'URL
	$url_info = parse_url($url);
	// Netoie le document de code unutile
	$content = cleanDocument($url, $content);
	
	if (isset ($url_info['scheme']))
		$metadata['scheme'] = $url_info['scheme'];
	if (isset ($url_info['host']))
		$metadata['host'] = $url_info['host'];
	if (isset ($url_info['path']))
		$metadata['path'] = $url_info['path'];
	if (isset ($url_info['query']))
		$metadata['query'] = $url_info['query'];

	// Keywords
	if (preg_match('#<meta +name *=[\"\']?keywords[\"\']?.*?content=[\"\']?([^<>\'\"]+)[\"\']?#si', $html_head, $match)) {
		$result = trim($match[1]);
		$metadata['keywords'] = $result;
	}

	// Description
	if (preg_match('#<meta +name *=[\"\']?description[\"\']?.*?content=[\"\']?([^<>\'\"]+)[\"\']?#si', $html_head, $match)) {
		$result = trim($match[1]);
		$metadata['description'] = $result;
	}

	// BASE
	if (preg_match('#<base +href *= *[\"\']?([^<>\'\"]+)[\"\']?#si', $html_head, $match)) {
		$result = trim($match[1]);
		$metadata['base'] = $result;
	}

	// Robots
	if (preg_match('#<meta +name *=[\"\']?robots[\"\']?.*?content=[\"\']?([^<>\'\"]+)[\"\']?#si', $html_head, $match)) {
		$result = trim($match[1]);
		$metadata['robot'] = $result;
	}

	// Recherche dans les tags	
	$words = array();
	foreach ($GLOBALS['weight_intags'] as $key => $value) {
		$metadata[$key] = strip_tags(getOnlyTagContent($key, $content));
		//$metadata["$key"."_words"] = wordsWeightToArray($GLOBALS['weight_intags'][$key],$metadata[$key]);
		$words = wordsWeightToArray($words,$key,$metadata[$key]);
	}
	
	// Supprime les mots précédament trouvé dans les tags pour ne garder que les mots de la page
	foreach ($GLOBALS['weight_intags'] as $key => $value) {
		$content = removeTagContent($key, $content);
	}

	$metadata['mybody'] = strip_tags(convertHtmlEntitieToText($content));
	//$metadata['mybody_words'] = wordsWeightToArray($words,'mybody',strip_tags(convertHtmlEntitieToText($content)));
	$words = wordsWeightToArray($words,'mybody',strip_tags(convertHtmlEntitieToText($content)));

	// Calcule le poid total
	foreach ($words as $word => $value) {
		$words[$word]['total']['density'] = 0;
		$words[$word]['total']['weight'] = 0;
		foreach ($GLOBALS['weight_intags'] as $key => $tempvalue) {
			if (isset($value[$key])) {
				$words[$word]['total']['density'] += $value[$key]["density"];
				$words[$word]['total']['weight'] += $value[$key]["weight"];
			}
		}
		
		$words[$word]['total']['avg_density'] = $words[$word]['total']['density']/count($GLOBALS['weight_intags']);
		$words[$word]['total']['avg_weight'] = $words[$word]['total']['weight']/count($GLOBALS['weight_intags']);
	} 

	$metadata['words'] = $words;

	/*// Recherche les mots unique
	foreach ($GLOBALS['weight_intags'] as $key => $value) {
		$uniquewords = array_keys($metadata["$key"."_words"]);
	}
	print "UNIQUE WORD ######<br> ";
	var_dump($uniquewords);exit;

	// Calcule la somme des weigts pour en faire qu'un
	foreach ($GLOBALS['weight_intags'] as $key => $value) {
		foreach ($metadata["$key"."_words"] as $word) {
			if (!isset($metadata['index'][$word])) {
				$metadata['index'][$word]['weight'] = 1;//$metadata["$key"."_words"][$word]['weight'];	
			} else {
				$metadata['index'][$word]['weight'] += 1;//$metadata["$key"."_words"][$word]['weight'];	
			}
		}
	}*/

	//$content = clearUTF($content);
	return $metadata;
}

/*function extractURLDomainFrom($url)
{
	$url_info = parse_url($url);

	return $url_info['scheme'].'://'.$url_info['host'];
}


function extractDomainWithPortFromURL($url)
{
	$url_info = parse_url($url);

	if (!isset($url_info['port']) || (isset($url_info['port']) && $url_info['port']!=80)) {
		$port = "";
	} else {
		$port = ":".$url_info['port'];
	}

	return extractURLDomainFrom($url).$port;
}

function extractPathFromURL($url)
{
	$url_info = parse_url($url);
	$path = $url_info['path'];

	$pos = strrpos($path,'/');
	$path = substr($path,1,$pos);
	print "POSI $pos $path";exit;


	// URL /test.php OR /test.php?test/toto
	preg_match('#^(/[^\?\/]+)+/#',$path,$match);
	
	return extractDomainWithPortFromURL($url).$path;
}
*/

// Retour l'url sans le nom du fichier
function urlWithoutFile($url) {
	$pos = strrpos($url, '/');
	$url = substr($url, 0, $pos +1);

	return $url;
}

// Supprime le dernier message d'erreur
function noError() {
	@trigger_error("");
}

// Test si il y'a une erreur'
function isError() {
	$error = error_get_last();
	return $error["message"] != "";
}

// Afficha la derniere erreur
function showError() {
	if (isError()) {
		print "<b>error</b></br>";
		var_dump(error_get_last());
	}
}

// Affiche un message et libere le buffer
function showInformation($text) {
	print "$text";
	flush();
	ob_flush();
}

// Extrait les URLs contenu dans un document HTML
function extract_links($src_url, $content) {
	$links = array ();

	showInformation("$src_url<br>");
	// Nettoie le document et r�cupere les URLs
	$base = urlWithoutFile($src_url);
	showElapsedTime('extract_links urlWithoutFile');
	$content = cleanDocument($base, $content);
	showElapsedTime('extract_links cleanDocument');
	//preg_match_all("#href=[\"\'](.*?)[\"\']#i", $content, $urls, PREG_SET_ORDER);
	preg_match_all("#<a *.*?href=[\'](.*?)[\'].*?>(.*?)</a>#si", $content, $urls1, PREG_SET_ORDER);
	showElapsedTime('extract_links preg_match_all1');
	preg_match_all("#<a *.*?href=[\"](.*?)[\"].*?>(.*?)</a>#si",$content, $urls2, PREG_SET_ORDER);
	showElapsedTime('extract_links preg_match_all2');

	// Fusione les 2 tableaux d'url
	foreach ($urls1 as $url ) {
		if (!isset($urls[$url[1]]) && strlen($url[1])<255) {
			$urls[] = $url;
		}				
	}
	showElapsedTime('extract_links foreach1');

	foreach ($urls2 as $url ) {
		if (!isset($urls[$url[1]]) && strlen($url[1])<255) {
			$urls[] = $url;
		}				
	}
	showElapsedTime('extract_links foreach2');
	

	foreach ($urls as $url) {
		// On convertir l'URL en absolu et on teste sans l'hote si on as mailto, etc ..'
		$absurl = absoluteURL($src_url,trim($url[1]));
		/*print "base avant: $src_url<br>";
		print "avant: $url[1]<br>";
		print "apres: $absurl<br>";*/
		$wordsfromlink = convertToUTF('UTF-8',strip_tags(convertHtmlEntitieToText(($url[2])))); 
		$tmpurl = trim(str_replace($base, "", $absurl));

		// On prend seulement les URLs ne contenant les scheme suivant
		if (!preg_match('#^(mailto|javascript|news|ftp):.*#si', $tmpurl)) {
			// Suprime les anchors
			/*if (preg_match('|#[^/]+$|', $absurl)) {
				$absurl = preg_replace('|(#[^/]+)$|', '', $absurl);
			}*/

			// On Nettoit le lien
			$absurl = urldecode($absurl);
			// On verifie et ajoute les URLs
			$words = array();
			$words =  wordsToArray($wordsfromlink);
			$GLOBALS['autoincrement'] = $GLOBALS['autoincrement'] + 1; 
			if (!isset ($links[$absurl])) {
				$links[$absurl]['temp_id'] = $GLOBALS['autoincrement'];
				$links[$absurl]['freq'] = 1;
				$links[$absurl]['words'] = $words;
			} else {
				$links[$absurl]['freq'] = $links[$absurl]['freq'] + 1;
				$links[$absurl]['words'] = array_merge($links[$absurl]['words'],$words);
			}
		}
	}
	showElapsedTime('extract_links foreach3');

	return $links;
}

function extract_links1($src_url, $content) {
	$links = array ();
	$urls = array();

	// Nettoie le document et r�cupere les URLs
	$base = urlWithoutFile($src_url);
	$content = cleanDocument($base, $content);

	showElapsedTime('extract_links clean');

	preg_match_all("#<a .*?>.*?</a>#si", $content, $match_urls, PREG_SET_ORDER);
	foreach ($match_urls as $item => $value) {
		$match=array();
		if (preg_match("#<a *.*?href=[\'](.*?)[\'].*?>(.*?)</a>#si",$value[0],$match)>0) {
			$urls[] = $match;
		} else {
			if (preg_match("#<a *.*?href=[\"](.*?)[\"].*?>(.*?)</a>#si",$value[0],$match)>0) {
				$urls[] = $match;			
			}
		} 
	}
	showElapsedTime('extract_links parse');

	
	

	foreach ($urls as $url) {
		// On convertir l'URL en absolu et on teste sans l'hote si on as mailto, etc ..'
		$absurl = absoluteURL($src_url,trim($url[1]));
		/*print "base avant: $src_url<br>";
		print "avant: $url[1]<br>";
		print "apres: $absurl<br>";*/
		$wordsfromlink = convertToUTF('UTF-8',strip_tags(convertHtmlEntitieToText(($url[2])))); 
		$tmpurl = trim(str_replace($base, "", $absurl));

		// On prend seulement les URLs ne contenant les scheme suivant
		if (!preg_match('#^(mailto|javascript|news|ftp):.*#si', $tmpurl)) {
			// Suprime les anchors
			/*if (preg_match('|#[^/]+$|', $absurl)) {
				$absurl = preg_replace('|(#[^/]+)$|', '', $absurl);
			}*/

			// On Nettoit le lien
			$absurl = urldecode($absurl);
			// On verifie et ajoute les URLs
			$words = array();
			$words =  wordsToArray($wordsfromlink);
			$GLOBALS['autoincrement'] = $GLOBALS['autoincrement'] + 1; 
			if (!isset ($links[$absurl])) {
				$links[$absurl]['temp_id'] = $GLOBALS['autoincrement'];
				$links[$absurl]['freq'] = 1;
				$links[$absurl]['words'] = $words;
			} else {
				$links[$absurl]['freq'] = $links[$absurl]['freq'] + 1;
				$links[$absurl]['words'] = array_merge($links[$absurl]['words'],$words);
			}
		}
	}
	showElapsedTime('extract_links foreach');
	

	return $links;
}





// source http://www.hiveminds.co.uk/book/print/816
function convertHtmlEntitieToText($content)
{
	$entities_src = array (
    "&nbsp;", //" "
    "&iexcl;", //"¡"
    "&cent;", //"¢"
    "&pound;", //"£"
    "&curren;", //"¤"
    "&yen;", //"¥"
    "&brvbar;", //"¦"
    "&sect;", //"§"
    "&uml;", //"¨"
    "&copy;", //"©"
    "&ordf;", //"ª"
    "&laquo;", //"«"
    "&not;", //"¬"
    "&shy;", //"­"
    "&reg;", //"®"
    "&macr;", //"¯"
    "&deg;", //"°"
    "&plusmn;", //"±"
    "&sup2;", //"²"
    "&sup3;", //"³"
    "&acute;", //"´"
    "&micro;", //"µ"
    "&para;", //"¶"
    "&middot;", //"·"
    "&cedil;", //"¸"
    "&sup1;", //"¹"
    "&ordm;", //"º"
    "&raquo;", //"»"
    "&frac14;", //"¼"
    "&frac12;", //"½"
    "&frac34;", //"¾"
    "&iquest;", //"¿"
    "&Agrave;", //"À"
    "&Aacute;", //"Á"
    "&Acirc;", //"Â"
    "&Atilde;", //"Ã"
    "&Auml;", //"Ä"
    "&Aring;", //"Å"
    "&AElig;", //"Æ"
    "&Ccedil;", //"Ç"
    "&Egrave;", //"È"
    "&Eacute;", //"É"
    "&Ecirc;", //"Ê"
    "&Euml;", //"Ë"
    "&Igrave;", //"Ì"
    "&Iacute;", //"Í"
    "&Icirc;", //"Î"
    "&Iuml;", //"Ï"
    "&ETH;", //"Ð"
    "&Ntilde;", //"Ñ"
    "&Ograve;", //"Ò"
    "&Oacute;", //"Ó"
    "&Ocirc;", //"Ô"
    "&Otilde;", //"Õ"
    "&Ouml;", //"Ö"
    "&times;", //"×"
    "&Oslash;", //"Ø"
    "&Ugrave;", //"Ù"
    "&Uacute;", //"Ú"
    "&Ucirc;", //"Û"
    "&Uuml;", //"Ü"
    "&Yacute;", //"Ý"
    "&THORN;", //"Þ"
    "&szlig;", //"ß"
    "&agrave;", //"à"
    "&aacute;", //"á"
    "&acirc;", //"â"
    "&atilde;", //"ã"
    "&auml;", //"ä"
    "&aring;", //"å"
    "&aelig;", //"æ"
    "&ccedil;", //"ç"
    "&egrave;", //"è"
    "&eacute;", //"é"
    "&ecirc;", //"ê"
    "&euml;", //"ë"
    "&igrave;", //"ì"
    "&iacute;", //"í"
    "&icirc;", //"î"
    "&iuml;", //"ï"
    "&eth;", //"ð"
    "&ntilde;", //"ñ"
    "&ograve;", //"ò"
    "&oacute;", //"ó"
    "&ocirc;", //"ô"
    "&otilde;", //"õ"
    "&ouml;", //"ö"
    "&divide;", //"÷"
    "&oslash;", //"ø"
    "&ugrave;", //"ù"
    "&uacute;", //"ú"
    "&ucirc;", //"û"
    "&uuml;", //"ü"
    "&yacute;", //"ý"
    "&thorn;", //"þ"
    "&yuml;", //"ÿ"
    "&quot;", //"""
    "&lt;", //"<"
    "&gt;", //">"
    "&amp;", //"&"
    "&apos;" //"'"
	);

	$entities_dst = array (
    " ", //"&nbsp;"
    " ", //"&iexcl;"
    " ", //"&cent;"
    " ", //"&pound;"
    " ", //"&curren;"
    " ", //"&yen;"
    " ", //"&brvbar;"
    " ", //"&sect;"
    " ", //"&uml;"
    " ", //"&copy;"
    " ", //"&ordf;"
    " ", //"&laquo;"
    " ", //"&not;"
    "­ ", //"&shy;"
    " ", //"&reg;"
    " ", //"&macr;"
    " ", //"&deg;"
    " ", //"&plusmn;"
    " ", //"&sup2;"
    " ", //"&sup3;"
    " ", //"&acute;"
    " ", //"&micro;"
    " ", //"&para;"
    " ", //"&middot;"
    " ", //"&cedil;"
    " ", //"&sup1;"
    " ", //"&ordm;"
    " ", //"&raquo;"
    " ", //"&frac14;"
    " ", //"&frac12;"
    " ", //"&frac34;"
    " ", //"&iquest;"
    "A", //"&Agrave;"
    "A", //"&Aacute;"
    "A", //"&Acirc;"
    "A", //"&Atilde;"
    "A", //"&Auml;"
    "A", //"&Aring;"
    "AE", //"&AElig;"
    "C", //"&Ccedil;"
    "E", //"&Egrave;"
    "E", //"&Eacute;"
    "E", //"&Ecirc;"
    "E", //"&Euml;"
    "I", //"&Igrave;"
    "I", //"&Iacute;"
    "I", //"&Icirc;"
    "I", //"&Iuml;"
    " ", //"&ETH;"
    "N", //"&Ntilde;"
    "O", //"&Ograve;"
    "O", //"&Oacute;"
    "O", //"&Ocirc;"
    "O", //"&Otilde;"
    "O", //"&Ouml;"
    " ", //"&times;"
    " ", //"&Oslash;"
    "U", //"&Ugrave;"
    "U", //"&Uacute;"
    "U", //"&Ucirc;"
    "U", //"&Uuml;"
    " ", //"&Yacute;"
    " ", //"&THORN;"
    " ", //"&szlig;"
    "a", //"&agrave;"
    "a", //"&aacute;"
    "a", //"&acirc;"
    "a", //"&atilde;"
    "a", //"&auml;"
    "a", //"&aring;"
    " ", //"&aelig;"
    "c", //"&ccedil;"
    "e", //"&egrave;"
    "e", //"&eacute;"
    "e", //"&ecirc;"
    "e", //"&euml;"
    "i", //"&igrave;"
    "i", //"&iacute;"
    "i", //"&icirc;"
    "i", //"&iuml;"
    "o", //"&eth;"
    "n", //"&ntilde;"
    "a", //"&ograve;"
    "a", //"&oacute;"
    "a", //"&ocirc;"
    "a", //"&otilde;"
    "a", //"&ouml;"
    " ", //"&divide;"
    " ", //"&oslash;"
    "u", //"&ugrave;"
    "u", //"&uacute;"
    "u", //"&ucirc;"
    "u", //"&uuml;"
    "y", //"&yacute;"
    " ", //"&thorn;"
    "y", //"&yuml;"
    "\"", //"&quot;"
    "<", //"&lt;"
    ">", //"&gt;"
    "&", //"&amp;"
    "'" //"&apos;"
	);
	
	return str_replace($entities_src,$entities_dst,$content);
	
}

// http://codedump.jonasjohn.de/snippets/elapsed_microtime.htm
// mt_get: returns the current microtime
function mt_get(){
    global $mt_time;
    list($usec, $sec) = explode(" ", microtime());
    return ((float)$usec + (float)$sec);
}

// mt_start: starts the microtime counter
function mt_start(){
    global $mt_time; $mt_time = mt_get();
}

// mt_end: calculates the elapsed time
function mt_end($len=4){
    global $mt_time;
    $time_end = mt_get();
    return round($time_end - $mt_time, $len);
}

function strongKeyword($keywords,$content)
{
	$mempos = 0;

	// Cherche les mots dans les titres
	foreach ($keywords as $keyword) {
		// On as trouvé un mot
		$pos =  stripos($content,$keyword,$mempos);
		while ($pos !== FALSE) {
			$strong = "<strong>".substr($content,$pos,strlen($keyword))."</strong>"; 
			$tmp = substr($content,$mempos,$pos);
			$tmp .= $strong; 
			$tmp .= substr($content,$pos+strlen($keyword),255);
			$content = $tmp;
			$mempos =  $pos+strlen($strong);
			$pos =  stripos($content,$keyword,$mempos);
		}
	}
	return $content;	
}

?>
