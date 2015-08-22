<?php
	require_once('classes/classe_bancodados.inc');
	
	$bd = new mysql('localhost', 'root', '', 'cake');
	
	$id = $_POST['id'];
	
	$infoParaAtualizar = array (
		'title' => $_POST['title'],
		'body' => $_POST['body']
	);
	
	$resultado = $bd->atualizar('articles', 'id', $id, $infoParaAtualizar);

	//@TODO verificar o status se foi atualizado com sucesso
	//@TODO pegar o $_POST['posicao']
	//@TODO redirecionar para o registro correspondente 'exemplo_2_6.php?posicao=' (posicao que eu quero)
	//@TODO desafio: implementar uma forma de passar a mensagem de sucesso ou erro(estudar SESSION)
	
	var_dump($resultado);