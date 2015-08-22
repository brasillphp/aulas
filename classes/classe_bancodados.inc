<?php
/**
 * Classe Básica para acesso a Banco de dados
 *	@abstract
 */
abstract class BancoDados {
	protected $_Tipo = null;	// Definido por cada banco de dados
	protected $_Servidor = 'localhost';
	protected $_Porta = 0;
	protected $_Usuario;
	protected $_Senha;
	protected $_Banco;
	protected $_conn = false;
	protected $_dataset = false;
	protected $_numrows = -1;
	protected $_tupla = false;
	protected $_posatual = -1;
	protected $_ultimoerro = "";
	protected $_ind_case = CASE_UPPER;

	abstract public function Conectar();
	abstract public function executaSQL($_sql);

	//abstract protected function navegainterno($_pos);
	//abstract protected function proximointerno();
	//abstract public function escapeString($_str);
	//abstract public function getLimit($_arr);
	//abstract protected function SetAffectedRows();

	
	public function getConn(){
	if (! $this-> _conn)
	{ $this->SetConn();}
	
	return $this-> _conn;
	
	
	}
	public	function getservidor(){
		return $this->_servidor;
	}
	
	public	function getusuario(){
		return $this->_usuario;
	}
	
	public	function getsenha(){
		return $this->_senha;
	}
	
	public	function getbanco()
	{
		return $this->_Banco;
	}
	
	public	function setbanco($banco)
	{
		$this->_Banco = $banco;
	}
	
	public	function setservidor($valor){
		return $this->_servidor = $valor;
	}
	public	function setusuario($valor){
		return $this->_usuario = $valor;
	}
	
	public	function setsenha($valor){
		return $this->_senha = $valor;
	}
	
	public function Setconn(){
	
		if(!$this->_conn){
		$this->_conn = new mysqli(
			$this->getservidor(),
			$this->getusuario(),
			$this->getsenha(),
			$this->getbanco()		
		);
		
		
		} else {
		
			return $this->_conn;
		
		}
	
	
	}
	
	public function SetPorta($_porta) {
	}

	
	public function startTransaction() 
	{
		$this->executaSQL('START TRANSACTION');	
	}

	public function commit() 
	{
		$this->executaSQL('commit');
	}

	public function ROLLBACK() 
	{
		$this->executaSQL('ROLLBACK');
	}
	
	public function find($onde, $peloque, $qualvalor, $buscainterna = false)
	{

		$conector = ' = ';
		
		if($buscainterna && !is_numeric($qualvalor))
		{
			$conector = " LIKE ";
			$qualvalor = "%$qualvalor%";
		}
		
		if(!is_numeric($qualvalor))
		{
			$qualvalor = "'$qualvalor'";
		}
		
		$sql = "select * from $onde where $peloque $conector $qualvalor";
		
		$retorno = $this->executaSQL($sql);
		
		$this->SetNumRows($retorno);
		$this->SetResult($retorno);
		
		return $retorno;
		
	}
	
	public function SetNumRows($retorno)
	{
		$this->_numrows = $retorno->num_rows;
	}
	

	protected function isSELECT($_sql,$_res) {
	}

	public function setCase($_case=CASE_UPPER) {
	}

	public function getNumRows() 
	{	
		return $this->_numrows;
	}




	public function navega($registro) 
	{
		if($registro == 'primeiro')
		{
			return $this->primeiro();
		}
		if($registro == 'ultimo')
		{
			return $this->ultimo();
		}
		
		return $this->GetResultado($registro);	
	}
	
	
	public function primeiro() 
	{
		return $this->GetResultado(0);
	}
	
	public function GetResultado($registro) 
	{
		if($registro >=0 && $this->resultado->data_seek($registro))
		{
			return $this->resultado->fetch_assoc();
		}
		else if ($registro > 0)
		{
			return $this->ultimo();
		}
		else
		{
			return $this->primeiro();
		}
	}	
	
	public function SetResult($resultado)
	{
		$this->resultado = $resultado;
	}
	
	public function proximo() 
	{
		$this->SetAnterior();
		$this->SetAtual();
		$this->SetProximo();

		$resultSet = $this->GetResultado();
		
		return $resultSet->next_result();
	}
	
	public function GetAtual()
	{
		return $this->_posatual;
	}
	
	public function SetAnterior()
	{
		$this->_posanterior = $this->GetAtual();
	}
	
	public function SetAtual()
	{
		$this->_posatual = $this->GetAtual()+1;
	}
		
	public function anterior() 
	{
		$resultSet = $this->GetResultado();
		return $resultSet->next_result();
	}

	public function ultimo() 
	{
		$ultimo = $this->getNumRows()-1;
		return $this->GetResultado($ultimo);
	}

	public function transforma() {
	}
	
	public function getDadosAtual() {
	}

	public function getUltimoErro() {
	}

	public function converteDataToBD() {
	}

	public function converteDataHoraToBD() {
	}

	public function converteDataToHTML() {
	}

	public function converteDataHoraToHTML() {
	}
}

class mysql extends BancoDados {
	
   public function __construct($host = null, $user = null, $pwd = null, $base = null)
   {
	$this->setservidor($host);
	$this->setusuario($user);
	$this->setsenha($pwd);
	$this->setbanco($base);
   } 
   
   public function insert($nomeTabela, $arrCampos, $arrValores)
   {
   
//		if(count($arrCampos) != count($arrValores))
//		{
//		die('não permitido');
//		}
   
		$strCampos = implode(', ', $arrCampos);
		
		$totalArgumentos = func_num_args();
		
		$arrArgumentos= func_get_args();
		
		$arrTodosValores = array();
		
		function test_alter(&$item1)
		{
			$item1 = "'$item1'";
		}
		
		for($i=2; $i<$totalArgumentos; $i++)
		{
			array_walk($arrArgumentos[$i], 'test_alter');
			$strValores = '('. implode(', ', $arrArgumentos[$i]) .')';
			
			$arrStrTodosValores[] = $strValores;
		}
		
		$this->startTransaction();
		
		foreach($arrStrTodosValores as $strValorEmLoop)
		{
			$this->executaSQL("insert into $nomeTabela($strCampos) values $strValorEmLoop;");
		}
		
		$this->commit();
		
		return true;
   }
   
   
   public function Conectar(){
	return $this->getconn();
	
   }
   
   public function executaSQL($sql)
   {
		return $this->getconn()->query($sql);
   }
   
   public function atualizar($tableName, $colunaReferencia, $valorReferencia, $valoresParaAtualizar)
   {
		
		$arrValoresParaAtualizar = array();
		
		foreach($valoresParaAtualizar as $chave => $valor)
		{
			$arrValoresParaAtualizar[] = " $chave='$valor' ";
		}
   
		$strValoresParaAtualizar = implode(', ', $arrValoresParaAtualizar);
   
		$sql = "UPDATE $tableName SET $strValoresParaAtualizar WHERE $colunaReferencia=$valorReferencia";
		
		//@TODO incluir startTransaction
		//@TODO incluir executaSQL armaenando o retorno 
		//@TODO se executaSQL retoirnar sucesso, commit, se falha, ROLLBACK
		//@TODO retornar o resultado do executaSQL
		
		return $sql;
   }
   
   }



