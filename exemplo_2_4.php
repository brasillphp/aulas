<?php
	require_once('classes/classe_bancodados.inc');
	
	$bd = new mysql('localhost', 'root');

	$bd->startTransaction();
	
	$houveErro = false;
	
	$bd->executaSQL("use cake;");
	
	$execRet = $bd->executaSQL("insert into articles(title, body) values ('aluno 05', 'Rafael atrasado');");
	
	if(!$execRet) 
	{
		$houveErro = true;
	}
	
	$execRet = $bd->executaSQL("insert into articles(title, body) values ('aluno 06', 'Rafael sr.net');");
	if(!$execRet) 
	{
		$houveErro = true;
	}
	
	$execRet = $bd->executaSQL("insert into articles(title, body) values ('aluno 07', 'Carlos faster');");
	if(!$execRet) 
	{
		$houveErro = true;
	}
	
	$execRet = $bd->executaSQL("insert into articles(title, body) values ('aluno 08', 'Deise loka');");
	if(!$execRet) 
	{
		$houveErro = true;
	}
		
	if($houveErro) 
	{
		echo "Erro!";
		$bd->ROLLBACK();
	} 
	else 
	{
		echo "Tudo OK!";
		$bd->commit();
	}
	
//	echo $sql;
