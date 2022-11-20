<?php

require("phpMQTT.php");
require("config.php");

$topic = "iot/kendali";
$message = @$_GET['message'];

if (empty($message)) {
  $message = "TEST";
}

$mqtt = new bluerhinos\phpMQTT($host, $port, "ClientID" . rand());

if ($mqtt->connect(true, NULL, $username, $password)) {
  $mqtt->publish($topic, $message, 0);
  $mqtt->close();
} else {
  echo "Fail or time out";
}

echo "[$topic] mengirim messages: $message";
