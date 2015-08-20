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
	//abstract protected function SetNumRows();
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

	protected function isSELECT($_sql,$_res) {
	}

	public function setCase($_case=CASE_UPPER) {
	}

	public function getNumRows() {
	}

	public function transforma() {
	}

	public function navega() {
	}

	public function primeiro() {
	}

	public function proximo() {
	}

	public function anterior() {
	}

	public function ultimo() {
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
   
		if(count($arrCampos) != count($arrValores))
		{
		die('não permitido');
		}
   
		$strCampos = implode(', ', $arrCampos);
		function test_alter(&$item1)
		{
			$item1 = "'$item1'";
		}
		array_walk($arrValores, 'test_alter');
		
		$strValores = implode(', ', $arrValores);
		
		$sqlToInsert = "insert into $nomeTabela($strCampos) values ($strValores)";
		
//		echo $sqlToInsert;
		
		$this->startTransaction();
		$statusInsert = $this->executaSQL($sqlToInsert);
		$this->commit();
		
		return $statusInsert;
   }
   
   
   public function Conectar(){
	return $this->getconn();
	
   }
   
   public function executaSQL($sql)
   {
		return $this->getconn()->query($sql);
   }
   
   
   
   }



