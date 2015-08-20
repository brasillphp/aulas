<?php
	require_once('classes/classe_bancodados.inc');
	
	$bd = new mysql('localhost', 'root', '', 'cake');
	
	$insert = $bd->insert('articles', array('title', 'body'), array('aluno 120', 'novo nome'), array('aluno 220', 'novo nome'), array('aluno 320', 'novo nome'), array('aluno 420', 'novo nome'));	
	
	if($insert)
	{
		echo "inserido com sucesso";
	}
	else
	{
		echo "no no no no";
	}