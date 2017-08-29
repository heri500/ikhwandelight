<?php

function update_pembelian(){
	if (isset($_POST['id'])){
		if (isset($_POST['tanggalbeli'])){
			$idpembelian = explode('-', $_POST['id']);
			$jampembelian = $_POST['jampembelian'];
			$tglbelibaru = date('Y-m-d',strtotime($_POST['tanggalbeli'])).' '.$jampembelian;
			db_query("UPDATE pembelian SET tglpembelian='%s' WHERE idpembelian=%d", $tglbelibaru, $idpembelian[1]);
			if ($_POST['ubah'] == 'tanggal'){
				print $_POST['tanggalbeli'];
			}else{
				print $jampembelian;
			}
		}
	}else{
		$updateddata = new stdClass();
		$updateddata->error = 'ID Penbelian Empty';
		print $updateddata->error;
	}
	exit();	
}