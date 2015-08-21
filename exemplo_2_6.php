<?php
	require_once('classes/classe_bancodados.inc');
	
	$bd = new mysql('localhost', 'root', '', 'cake');
	
	$bd->find('articles', 'title', 'aluno',  true);
	
	var_dump($bd->navega($_GET['posicao']));