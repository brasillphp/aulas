<form method="POST" action="exemplo_2_6_edit.php">
	<input type="hidden" name="id" value="<?php echo $resultado[$posicao]['id']?>" />
	<input type="hidden" name="posicao" value="<?php echo $posicao ?>" />
	<fieldset>
	<legend> Dados do Registro </legend>
		<dl>
			<dt> <label for="title"> T�tulo</label> </dt>
			<dd> <input name="title" id="title" value="<?php echo $resultado[$posicao]['title']?>" placeholder="seu titulo aqui"> </dd>
		</dl>
	</fieldset>
	<fieldset>
	<legend> Conte�do </legend>
		<dl>
			<dt> <label for="body"> Conte�do </label> </dt>
			<dd> <input name="body" id="body" value="<?php echo $resultado[$posicao]['body']?>" placeholder="o body vai aqui"> </dd>
		<button type="submit">Enviar</button> 
		</dl>
	</fieldset>
</form>
