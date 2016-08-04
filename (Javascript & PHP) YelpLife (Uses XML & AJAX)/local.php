<?php
//This file is based off of sample.php from YELP
//Adjusted and fixed for my own use.
require_once('lib/OAuth.php');

//Variables
$CONSUMER_KEY = 'Yk2Ww2lPI5buoQMikz6Q7Q';
$CONSUMER_SECRET = 'ZPzMu5Cjy165u1CsXao0z-WAxOw';
$TOKEN = 'W-a5Mqtth_8bOk5LAKpLSE2otB_xMjcj';
$TOKEN_SECRET = 'HVxOQtF8_PRmZWsuvhofR3ZT6dc';
$API_HOST = 'api.yelp.com';
$DEFAULT_TERM = 'dinner';
$DEFAULT_LOCATION = 'San Francisco, CA';
$SEARCH_LIMIT = 10;
$SEARCH_PATH = '/v2/search/';

//Input from ajax
$locInput = $_GET['location'];
$termInput = $_GET['term'];

//calls the main function
query_api($termInput, $locInput);

//This passes the information and checks to make sure information was recieved
function query_api($term, $location) {
	
	$url_params = array();
    
    $url_params['term'] = $term ?: $GLOBALS['DEFAULT_TERM'];
    $url_params['location'] = $location?: $GLOBALS['DEFAULT_LOCATION'];
    $url_params['limit'] = $GLOBALS['SEARCH_LIMIT'];
    $search_path = $GLOBALS['SEARCH_PATH'] . "?" . http_build_query($url_params);
    
    $test = request($GLOBALS['API_HOST'], $search_path);

    $response = json_decode($test);
    $business_id = $response->businesses[0]->id;
	
	echo $test;
}

//communicates with the OAuth.php for the JSON information
function request($host, $path) {

    $unsigned_url = "https://" . $host . $path;
	
    $token = new OAuthToken($GLOBALS['TOKEN'], $GLOBALS['TOKEN_SECRET']);
	
    $consumer = new OAuthConsumer($GLOBALS['CONSUMER_KEY'], $GLOBALS['CONSUMER_SECRET']);
	
    $signature_method = new OAuthSignatureMethod_HMAC_SHA1();
    $oauthrequest = OAuthRequest::from_consumer_and_token(
        $consumer, 
        $token, 
        'GET', 
        $unsigned_url
    );
	
    $oauthrequest->sign_request($signature_method, $consumer, $token);
    
    $signed_url = $oauthrequest->to_url();
    
    try {
        $ch = curl_init($signed_url);
        if (FALSE === $ch)
            throw new Exception('Failed to initialize');
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_HEADER, 0);
        $data = curl_exec($ch);
        if (FALSE === $data)
            throw new Exception(curl_error($ch), curl_errno($ch));
        $http_status = curl_getinfo($ch, CURLINFO_HTTP_CODE);
        if (200 != $http_status)
            throw new Exception($data, $http_status);
        curl_close($ch);
    } catch(Exception $e) {
        trigger_error(sprintf(
            'Curl failed with error #%d: %s',
            $e->getCode(), $e->getMessage()),
            E_USER_ERROR);
    }
	
    return $data;
}

?>