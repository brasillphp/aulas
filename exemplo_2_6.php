<?php
	require_once('classes/classe_bancodados.inc');
	
	$bd = new mysql('localhost', 'root', '', 'cake');
	
	$resultado = $bd->find('articles', 'title', 'aluno',  true);
	
	$posicao = isset($_GET['posicao']) ? $_GET['posicao'] : 0;
	
	if(isset($_GET['posicao']))
	{
		$resultado = array($posicao => $bd->navega($posicao));
	}
	
//	var_dump($resultado);
//	die;

	if(isset($_GET['acao']) && $_GET['acao'] == "editar")
	{
		include('exemplo_2_6_form.php');
	}
	else
	{


?>

	<html>
	<table>
	<thead>
		<title>	Resultados BD </title>
			<tr>
				<td> ID: 	</td>
				<td> Title:	</td>
				<td> Body:	</td>
				<td> Editar:	</td>
				<td> Deletar:	</td>				
			</tr>	
	</thead>
	<tbody>
<?php
	foreach($resultado as $pos => $item)
	{
?>
			<tr>
				<td> <?php echo $item['id']; ?> </td>
				<td> <?php echo $item['title']; ?>	</td>
				<td> <?php echo $item['body']; ?>	</td>
				<td> <a href="?posicao=<?= $pos ?>&acao=editar"> Editar</a> </td>
				<td> <a href="?posicao=<?= $pos ?>&acao=deletar"> Deletar</a> </td>
			</tr>
<?php		
	}
	unset ($item);
	?>
	</tbody>
	</table>
	</html>
	
<?php
	}
	?>