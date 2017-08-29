<?php

function pembelian(){
	//set_default_time_zone();
	get_number_format($currencySym, $thousandSep, $decimalSep);
	createLogoImagePath();
	$path = drupal_get_path('theme', 'cti_flex');
 	$form_style = $path.'/css/custom-style.css';
 	drupal_add_css($form_style, 'theme', 'all', FALSE);
 	$variables['styles'] = drupal_get_css();
	drupal_add_css('misc/media/datatables/css/demo_table_jui.css');
	drupal_add_css('misc/media/themes/jquery-ui-1.8.11.custom.css');
	drupal_add_css('misc/media/css/validationEngine.jquery.css');
	drupal_add_js('misc/media/jquery-1.4.4.min.js');
	drupal_add_js('misc/media/jqClock.min.js');
	drupal_add_js('misc/media/jquery.validationEngine-en.js');
	drupal_add_js('misc/media/jquery.validationEngine.js');
	drupal_add_js('misc/media/jquery-ui-1.8.11.custom.min.js');
	drupal_add_js('misc/media/datatables/js/jquery.dataTables.min.js');
	drupal_add_js('misc/media/datatables/js/dataTables.addtr.js');
	drupal_add_js('misc/media/datatables/js/number.format.js');
	drupal_add_js('misc/media/jquery.autotab-1.1b.js');
	if (isset($_GET['tanggal'])){
		$tglsekarang = date("Y-m-d", strtotime($_GET['tanggal']));
		$tgltampil = date("d-m-Y", strtotime($_GET['tanggal']));
	}else{
		$tglsekarang = date("Y-m-d");
		$tgltampil = date("d-m-Y");
	}
	drupal_add_js(
		array(
			'tglsekarang' => $tglsekarang,
			'tgltampil' => $tgltampil,
		), 
	'setting');
	$js_path = drupal_get_path('module','pembelian').'/js/pembelian.js';
	drupal_add_js($js_path);
	$panduantombol = '<a style="font-weight: bold;text-align: center;">Ctrl+Shift+</a>';
	$tombolcari = '<a id="tombolubahharga" class="cari" onclick="ubahharga()">F2:UBAH HARGA</a>';
	$tombolqty = '<a id="tombolubahqty" onclick="ubahqty()" class="buttonqty">F3:UBAH QTY</a>';
	$tombolhapus = '<a class="buttonhapus" onclick="hapus_latest_produk()" title="Hapus produk">F4:HAPUS</a>';
	$tombolselesai = '<a class="buttonselesai" onclick="kirim_data()">F5:SELESAI</a>';
	$tombolprint = '<a class="buttonprint" onclick="kirim_data()">F6:SELESAI & PRINT</a>';
	$pembelian = '<button onclick="munculkankasir();" style="font-size:12px;border: 1px solid orangered;">'.strtoupper("Klik untuk memunculkan form pembelian").'</button>';
	$pembelian .= '<div id="dialogkasir" style="font-size: 12px;" title="GLOBAL POS PEMBELIAN ['.$tgltampil.']">';
	$pembelian .= '<div id="info-kasir-waktu">';
	$pembelian .= '<div id="tempattanggalkasir">';
	$pembelian .= '<div id="tempattanggal">';
	$pembelian .= '<label>TANGGAL</label><input readonly="readonly" type="text" id="tglbeli" name="tglbeli" value="'.$tgltampil.'">';
	$pembelian .= '<input type="hidden" id="tglbelikirim" name="tglbelikirim" value="'.$tglsekarang.'">';
	$pembelian .= '</div>';
	$pembelian .= '<div id="tempatnamakasir">';
	global $user;
	$pembelian .= '<label>KASIR</label><input readonly="readonly" type="text" id="kasir" name="kasir" value="'.$user->name.'">';
	$pembelian .= '</div>';
	$pembelian .= '</div>';
	$pembelian .= '<div id="tempatjam" align="center">';
	$pembelian .= 'Jam';
	$pembelian .= '</div>';
	$pembelian .= '<div id="tempatkosong">';
	$pembelian .= '<div id="tempatsupplier"><label>SUPPLIER</label></div>';
	$pembelian .= '<div id="tempatsupplier2">'.createSupplierSelection().'</div>';
	$pembelian .= '</div>';
	$pembelian .= '</div>';
	$pembelian .= '<div id="barcode_place">SCAN ATAU INPUT BARCODE, KODE ATAU NAMA PRODUK : ';
	$pembelian .= '<input type="text" id="barcode" name="barcode" class="barcodekasir">';
	$pembelian .= '<input type="hidden" id="hiddenbarcode" name="hiddenbarcode"></div>';
	$pembelian .= '<div id="tempattabelkasir">'.view_kasir_pembelian().'</div>';
	$pembelian .= '<input type="hidden" id="last_id" name="last_id"><input type="hidden" id="lastqty" name="lastqty" value="1"><input type="hidden" id="lastharga" name="lastharga">';
	$pembelian .= '<input type="hidden" id="nilaikirim" name="nilaikirim">';
	$pembelian .= '<div id="tempattombolkasir" style="height: 340px;">';
	$pembelian .= $panduantombol;
	$pembelian .= $tombolcari;
	$pembelian .= $tombolqty;
	$pembelian .= $tombolhapus;
	$pembelian .= $tombolselesai;
	$pembelian .= $tombolprint;
	$pembelian .= '</div>';
    $pembelian .= '<div id="tempattotal"><div id="totalbelanja">Total Belanja : '.$currencySym.' 0</div></div>';
	$pembelian .= '</div>';
	$pembelian .= '<div title="Informasi" id="dialogwarning">';
	$pembelian .= '<p id="pesantext">Produk yang dicari tidak ada, Silahkan masukkan Barcode/Kode Produk/Nama Produk yang lain...!!!</p>';
	$pembelian .= '<p style="text-align: center"><button id="tutupdialog" class="buttonwarning" onclick="tutupwarning();">CLOSE</button></p>';
	$pembelian .= '</div>';
	$pembelian .= '<div title="UBAH HARGA BELI" id="dialogubahharga">';
	$pembelian .= '<label>Harga Baru : </label><input type="text" id="newharga" name="newharga" value="1">';
	$pembelian .= '</div>';
	$pembelian .= '<div title="UBAH QTY" id="dialogubahqty">';
	$pembelian .= '<label>Qty Baru : </label><input type="text" id="newqty" name="newqty" value="1">';
	$pembelian .= '</div>';
	$pembelian .= '<div title="UBAH QTY" id="dialogubahqty2">';
	$pembelian .= '<label>Qty Baru : </label><input type="text" id="newqty2" name="newqty2">';
	$pembelian .= '</div>';
	$pembelian .= '<div title="PEMBAYARAN" id="dialogbayar">';
	$carabayar = '<select id="carabayar" name="carabayar">';
	$result = db_query("SELECT carabayar FROM carabayar");
	$i = 0;
	while($data = db_fetch_object($result)){
		if ($i == 0){
			$carabayar .= '<option selected="selected" value="'.$data->carabayar.'">'.$data->carabayar.'</option>';	
		}else{
			$carabayar .= '<option value="'.$data->carabayar.'">'.$data->carabayar.'</option>';	
		}
		$i++;
	}
	$carabayar .= '</select>';
	$nilaibayar = '<input type="text" id="nilaibayar" name="nilaibayar">';
	$kembali = '<input readonly="readonly" type="text" id="kembali" name="kembali">';
	$totalbelanja = '<input type="text" id="totalbelanjauser" name="totalbelanjauser">';
	$pembelian .= '<div class="barisbayar"><label>Total Belanja</label>'.$totalbelanja.'</div>';
	$pembelian .= '<div class="barisbayar"><label>Cara Bayar</label>'.$carabayar.'</div>';
	$pembelian .= '<div class="barisbayar"><label>Pembayaran</label>'.$nilaibayar.'</div>';
	$pembelian .= '<div id="bariskembali" class="barisbayar"><label>Kembali</label>'.$kembali.'</div>';
	$pembelian .= '</div>';
	return $pembelian;
}

function simpan_pembelian(){
	//nonota, idpemakai, total, bayar, kembali
	if ($_POST["detail_produk"] AND $_POST["bayar"] >= 0 AND $_POST["totalbelanja"]){
		$result = db_query("SELECT idpembelian FROM pembelian ORDER BY idpembelian DESC LIMIT 1");
		$data = db_fetch_object($result);
		if ($data->idpembelian > 0){
			$next_id = $data->idpembelian + 1;
		}else{
			$next_id = 1;
		}
		$no_nota = buat_nota($next_id);
		$kembali = $_POST["bayar"] - $_POST["totalbelanja"];
		date_default_timezone_set('Asia/Jakarta');
		$waktujual = $_POST["tglbeli"]." ".date("H:i:s");
		$caraBayar = $_POST["carabayar"];
		global $user;
		db_query("INSERT INTO pembelian (nonota, idpemakai, total, bayar, kembali, tglpembelian, carabayar) VALUES ('%s', '%d', '%f', '%f', '%f', '%s', '%s')",
		$no_nota, $user->uid, $_POST["totalbelanja"], $_POST["bayar"], $kembali, $waktujual, $caraBayar);
		$next_id = db_last_insert_id('pembelian', 'idpembelian');
		print $_POST["detail_produk"];
		if ($kembali < 0){
			db_query("INSERT INTO detailhutang (idsupplier, idpembelian, besarhutang) VALUES ('%d','%d','%f')",
			$_POST["idsupplier"],$next_id,abs($kembali));
			$resultpiutang = db_query("SELECT idsupplier, besarhutang  FROM hutang WHERE idsupplier='%d'",
			$_POST["idsupplier"]);
			$datapiutang = db_fetch_object($resultpiutang);
			if ($datapiutang->idsupplier){
				$besarhutangskrg = $datapiutang->besarhutang + abs($kembali);
				db_query("UPDATE hutang SET besarhutang='%f',uid='%d' WHERE idsupplier='%d'",
				$besarhutangskrg,$user->uid,$_POST["idsupplier"]);
			}else{
				db_query("INSERT INTO hutang(idsupplier,besarhutang,uid)VALUES('%d','%f','%d')",
				$_POST["idsupplier"],abs($kembali),$user->uid);	
			}
		}
		$pecahdetail = explode("&",$_POST["detail_produk"]);
		$totalmodal = 0;
		foreach ($pecahdetail as $parameter){
			$pecahparameter = explode("=",$parameter);
			$pecahnilai = explode("___",remove_utf8_bom($pecahparameter[1]));
			$IDPRODUK =	$pecahnilai[0];
			$QTY = $pecahnilai[1];
			$HARGABELI = $pecahnilai[2];
			$result = db_query("SELECT hargapokok,stok FROM product WHERE idproduct='%d'",$IDPRODUK);	
			$data = db_fetch_object($result);
			$HARGAPOKOK = $data->hargapokok;
			$STOKSEBELUM = $data->stok;
			//idpembelian, idproduct, jumlah, hargapokok, hargapokok
			db_query("INSERT INTO detailpembelian(idpembelian, idproduct, jumlah, hargapokok, hargapokoksebelumnya) VALUES
			('%d', '%d', '%f', '%f','%f')",
			$next_id,$IDPRODUK,$QTY,$HARGABELI,$HARGAPOKOK);
			if ($HARGAPOKOK <> $HARGABELI){
				db_query("INSERT INTO historyhargabeli (hargasebelum, hargasesudah, uid) VALUES('%f','%f','%d')",
				$HARGAPOKOK,$HARGABELI,$user->uid);
				db_query("UPDATE product SET hargapokok='%f' WHERE idproduct='%d'",$HARGABELI,$IDPRODUK);
			}
			$STOKSEKARANG = $STOKSEBELUM + $QTY;
			db_query("UPDATE product SET stok='%f' WHERE idproduct='%d'",$STOKSEKARANG,$IDPRODUK);
			$KETERANGAN = 'Pembelian';
			db_query("INSERT INTO transaksistock (idproduk, idpembelian, stocksebelum, masuk, stocksetelah, keterangan) VALUES 
			('%d', '%d', '%f', '%f', '%f', '%s')",$IDPRODUK,$next_id,$STOKSEBELUM,$QTY,$STOKSEKARANG,$KETERANGAN);
		}
	}else{
		print 'error';	
	}
	exit();
}
function buat_nota($idpembelian){
	if ($idpembelian > 0 AND $idpembelian < 10){
		$no_nota = "F000000".$idpembelian;	
	}elseif ($idpembelian >= 10 AND $idpembelian < 100){
		$no_nota = "F00000".$idpembelian;	
	}elseif ($idpembelian >= 100 AND $idpembelian < 1000){
		$no_nota = "F0000".$idpembelian;	
	}elseif ($idpembelian >= 1000 AND $idpembelian < 10000){
		$no_nota = "F000".$idpembelian;	
	}elseif ($idpembelian >= 10000 AND $idpembelian < 100000){
		$no_nota = "F00".$idpembelian;	
	}elseif ($idpembelian >= 100000 AND $idpembelian < 1000000){
		$no_nota = "F0".$idpembelian;	
	}elseif ($idpembelian >= 1000000){
		$no_nota = "F".$idpembelian;	
	}
	return $no_nota;
}
function cari_produk_pembelian(){
	if ($_POST["katacari"]){
		$KATACARI = '%'.$_POST["katacari"].'%';
		if (isset($_GET["idsupplier"]) && !empty($_GET["idsupplier"]) && $_GET["idsupplier"] != 'null'){
			$result = db_query("SELECT idproduct,barcode,namaproduct,hargapokok,stok FROM product WHERE (alt_code LIKE '%s' OR barcode LIKE '%s' OR UPPER(namaproduct) LIKE '%s') AND idsupplier='%d'",$KATACARI,$KATACARI,$KATACARI,$_GET["idsupplier"]);
		}else{
			$result = db_query("SELECT idproduct,barcode,namaproduct,hargapokok,stok FROM product WHERE alt_code LIKE '%s' OR barcode LIKE '%s' OR UPPER(namaproduct) LIKE '%s'",$KATACARI,$KATACARI,$KATACARI);
		}
		$data = db_fetch_object($result);
		if ($data->idproduct){
			print $data->idproduct.';'.$data->namaproduct.';'.$data->hargapokok.';'.$data->stok.';'.$data->barcode;
		}else{
			print "error";
		}
	}
	exit();	
}
function cari_barang_pembelian(){
	if ($_GET["term"]){
		$KATACARI = '%'.$_GET["term"].'%';
		if (isset($_GET["idsupplier"]) && !empty($_GET["idsupplier"]) && $_GET["idsupplier"] != 'null'){
			$result = db_query("SELECT barcode, namaproduct FROM product WHERE (alt_code LIKE '%s' OR barcode LIKE '%s' OR UPPER(namaproduct) LIKE '%s') AND idsupplier='%d' LIMIT 50",$KATACARI,$KATACARI,$KATACARI,$_GET["idsupplier"]);
		}else{
			$result = db_query("SELECT barcode, namaproduct FROM product WHERE alt_code LIKE '%s' OR barcode LIKE '%s' OR UPPER(namaproduct) LIKE '%s' LIMIT 50",$KATACARI,$KATACARI,$KATACARI);
		}
		$items = array();
		while ($data = db_fetch_object($result)){
			$items[] = array('value' => $data->namaproduct,'barcode' => $data->barcode,'alt_code' => $data->alt_code);
		}
		print json_encode($items);
	}
	exit();	
}
function view_kasir_pembelian(){
	$kasirtabel ='<table cellpadding="0" cellspacing="0" border="0" class="display" id="tabel_kasir">';
	$kasirtabel .= '<thead>';
	$kasirtabel .= '<tr>';
	$kasirtabel .= '<th class="tablebutton"></th>';
	$kasirtabel .= '<th class="tablebutton"></th>';
	$kasirtabel .= '<th>PRODUK</th>';
	$kasirtabel .= '<th>HARGA</th>';
	$kasirtabel .= '<th class="qty">QTY</th>';
	$kasirtabel .= '<th class="subtotal">SUBTOTAL</th>';
	$kasirtabel .= '<th class="qty">STOK</th>';
	$kasirtabel .= '</tr>';
	$kasirtabel .= '</thead>';
	$kasirtabel .= '<tbody>';
	$kasirtabel .= '</tbody>';
	$kasirtabel .= '</table>';
	return $kasirtabel;
}
function view_tabel_pembelian(){
    get_number_format($currencySym, $thousandSep, $decimalSep);
	$path = drupal_get_path('theme', 'cti_flex');
 	$form_style = $path.'/css/custom-style.css';
 	drupal_add_css($form_style, 'theme', 'all', FALSE);
 	$variables['styles'] = drupal_get_css();
	if ($_POST["tgl1"] AND $_POST["tgl2"]){
		$tgl1 = $_POST["tgl1"];
		$tgl2 = $_POST["tgl2"];
	}else{
		$tgl1 = date("Y-m-").'01';
		$tgl2 = date("Y-m-d");	
	}
	if ($_POST["pilihantampil"] == 'NOTA'){
		$nota = 'selected="selected"';
		$tabeltampil = tabel_pembelian($tgl1,$tgl2);
		$urutan = 1; 
	}elseif ($_POST["pilihantampil"] == 'PRODUK'){
		$produk = 'selected="selected"';
		$tabeltampil = pembelian_produk($tgl1,$tgl2);
		$urutan = 2;
	}else{
		$tabeltampil = tabel_pembelian($tgl1,$tgl2);
		$nota = 'selected="selected"';
		$urutan = 1;
	}
	drupal_add_css('misc/media/datatables/css/demo_table_jui.css');
	drupal_add_css('misc/media/datatables/css/TableTools.css');
	drupal_add_css('misc/media/datatables/themes/smoothness/jquery-ui-1.8.4.custom.css');
	drupal_add_css('misc/media/datatables/css/ColVis.css');
	_addJqueryPlugins();
	drupal_add_js('misc/media/jquery-ui-1.8.custom.min.js');
	_addTimePickerPlugins();
	_addJeditablePlugins();
	_addAutotabPlugins();
	drupal_add_js('misc/media/datatables/js/jquery.dataTables.min.js');
	drupal_add_js('misc/media/datatables/js/ColVis.min.js');
	drupal_add_js('misc/media/datatables/ZeroClipboard/ZeroClipboard.js');
	drupal_add_js('misc/media/datatables/js/TableTools.min.js');
	drupal_add_js(
		array(
			'urutan' => $urutan,
		), 
	'setting');
	$js_path = drupal_get_path('module','pembelian').'/js/tabel.pembelian.js';
	drupal_add_js($js_path);
	$pilihantampil = '<select id="pilihantampil" name="pilihantampil">';
	$pilihantampil .= '<option '.$nota.'>NOTA</option>';
	$pilihantampil .= '<option '.$produk.'>PRODUK</option>';
	$pilihantampil .= '</select>';
	$pilihperiode = '<form action="'.base_path().'pembelian/viewpembelian" method="post"><div id="pilihanperiode"><label>PILIH PERIODE PEMBELIAN </label><input readonly="readonly" type="text" id="tgl1" name="tgl1" value="'.date('d-m-Y', strtotime($tgl1)).'">';
	$pilihperiode .= '<input readonly="readonly" type="text" id="tgl2" name="tgl2" value="'.date('d-m-Y', strtotime($tgl2)).'">'.$pilihantampil.'<button>LIHAT PEMBELIAN</button></div></form>';
	$viewpembelian = $pilihperiode.'<div id="viewpembelian">'.$tabeltampil.'</div>';
	$viewpembelian .= '<div id="dialogdetail" title="DETAIL PEMBELIAN"></div>';
	return $viewpembelian;
}

function tabel_pembelian($tgl1,$tgl2){
    get_number_format($currencySym, $thousandSep, $decimalSep, false);
	//nonota, tglpembelian, idpemakai, idlangganan, total, 
	//totalmodal, carabayar, bayar, kembali
	$tgl1 = date('Y-m-d', strtotime($tgl1));
	$tgl2 = date('Y-m-d', strtotime($tgl2));
	$tabelpembelian ='<table cellpadding="0" cellspacing="0" border="0" class="display" id="tabel_pembelian">';
	$tabelpembelian .= '<thead>';
	$tabelpembelian .= '<tr>';
	$tabelpembelian .= '<th class="tablebutton"></th>';
	if (cekUserRoles()){
		$tabelpembelian .= '<th class="tablebutton"></th>';
	}
	$tabelpembelian .= '<th>NO. NOTA</th>';
	$tabelpembelian .= '<th class="tanggal">HARI</th>';
	$tabelpembelian .= '<th class="tanggal">TGL</th>';
	$tabelpembelian .= '<th class="tanggal">JAM</th>';
	if (cekUserRoles()){
		$tabelpembelian .= '<th>TOTAL</th>';
		$tabelpembelian .= '<th>BAYAR</th>';
		$tabelpembelian .= '<th>KEMBALI</th>';
		$tabelpembelian .= '<th>KASIR</th>';
	}
	$tabelpembelian .= '</tr>';
	$tabelpembelian .= '</thead>';
	$tabelpembelian .= '<tbody>';
	$result = db_query("SELECT idpembelian, name, nonota, SUBSTR(tglpembelian,1,10) AS tanggal,SUBSTR(tglpembelian,11,6) AS waktu, idpemakai, total, bayar, kembali FROM
	pembelian a, cms_users b WHERE a.idpemakai = b.uid AND SUBSTR(tglpembelian,1,10) BETWEEN '%s' AND '%s' ORDER BY idpembelian",
	$tgl1,$tgl2);
	$totalmodal = 0;
	$totalbayar = 0;
	$totalkembali = 0;
	$arrayhari = arrayHari();
	drupal_add_js(
		array(
			'namahari' => $arrayhari,
		), 
	'setting');
	while($data = db_fetch_object($result)){
		$idpembelian = $data->idpembelian;
		$tabelpembelian .= '<tr>';
		$tomboldetail = '<img title="Klik untuk melihat detail pembelian" onclick="view_detail(\''.$data->idpembelian.'\',\''.$data->nonota.'\');" src="'.base_path().'misc/media/images/forward_enabled.ico">';
		$tombolhapus = '<img title="Klik untuk menghapus pembelian" onclick="delete_pembelian(\''.$data->idpembelian.'\',\''.$data->nonota.'\');" src="'.base_path().'misc/media/images/del.ico" width="22">';
		$tabelpembelian .= '<td class="center">'.$tomboldetail.'</td>';
		if (cekUserRoles()){
			$tabelpembelian .= '<td class="center">'.$tombolhapus.'</td>';
		}
		$tabelpembelian .= '<td class="center">'.$data->nonota.'</td>';
		$indexhari = date('w', strtotime($data->tanggal));
		$tabelpembelian .= '<td id="haripembelian-'.$idpembelian.'" class="center">'.$arrayhari[$indexhari].'</td>';
		$tabelpembelian .= '<td id="tglpembelian-'.$idpembelian.'" class="center edit-tanggal">'.date('d-m-Y', strtotime($data->tanggal)).'</td>';
		$tabelpembelian .= '<td id="jampembelian-'.$idpembelian.'" class="center edit-jam">'.$data->waktu.'</td>';
		if (cekUserRoles()){
			$tabelpembelian .= '<td class="angka">'.number_format($data->total,2,$decimalSep,$thousandSep).'</td>';
			$tabelpembelian .= '<td class="angka">'.number_format($data->bayar,2,$decimalSep,$thousandSep).'</td>';
			$tabelpembelian .= '<td class="angka">'.number_format($data->kembali,2,$decimalSep,$thousandSep).'</td>';
			$tabelpembelian .= '<td class="center">'.$data->name.'</td>';
		}
		$tabelpembelian .= '</tr>';
		$totalmodal = $totalmodal + $data->total;
		$totalbayar = $totalbayar + $data->bayar;
		$totalkembali = $totalkembali + $data->kembali;
	}
	$tabelpembelian .= '</tbody>';
	if (cekUserRoles()){
		$tabelpembelian .= '<tfoot>';
		$tabelpembelian .= '<tr>';
		$tabelpembelian .= '<th style="text-align:right" colspan="6">Total:&nbsp;&nbsp;</th>';
		$tabelpembelian .= '<th style="text-align: right">'.$currencySym.' '.number_format($totalmodal,2,$decimalSep,$thousandSep).'&nbsp;&nbsp;</th>';
		$tabelpembelian .= '<th style="text-align: right">'.$currencySym.' '.number_format($totalbayar,2,$decimalSep,$thousandSep).'&nbsp;&nbsp;</th>';
		$tabelpembelian .= '<th style="text-align: right">'.$currencySym.' '.number_format($totalkembali,2,$decimalSep,$thousandSep).'&nbsp;&nbsp;</th>';
		$tabelpembelian .= '<th></th>';
		$tabelpembelian .= '</tr>';
		$tabelpembelian .= '</tfoot>';
	}
	$tabelpembelian .= '</table>';
	return $tabelpembelian;
}

function detail_pembelian(){
	if ($_POST["idpembelian"]){
        get_number_format($currencySym, $thousandSep, $decimalSep, false);
		$tabelpembelian ='<table cellpadding="0" cellspacing="0" border="0" class="display" id="tabel_detail_pembelian">';
		$tabelpembelian .= '<thead>';
		$tabelpembelian .= '<tr>';
		$tabelpembelian .= '<th>BARCODE</th>';
		$tabelpembelian .= '<th>PRODUK</th>';
		$tabelpembelian .= '<th class="qty">QTY</th>';
		if (cekUserRoles()){
			$tabelpembelian .= '<th>H.MODAL</th>';
			$tabelpembelian .= '<th>SUBTOTAL</th>';
		}
		$tabelpembelian .= '</tr>';
		$tabelpembelian .= '</thead>';
		$tabelpembelian .= '<tbody>';
		$result = db_query("SELECT c.barcode, c.namaproduct, b.jumlah, b.hargapokok FROM 
		detailpembelian b, product c WHERE b.idproduct=c.idproduct AND b.idpembelian='%d'",$_POST["idpembelian"]);
		while($data = db_fetch_object($result)){
			$tabelpembelian .= '<tr>';
			$tabelpembelian .= '<td>'.$data->barcode.'</td>';
			$tabelpembelian .= '<td>'.$data->namaproduct.'</td>';
			$tabelpembelian .= '<td class="angka">'.$data->jumlah.'</td>';
			if (cekUserRoles()){
                $subtotal = $data->hargapokok * $data->jumlah;
				$tabelpembelian .= '<td class="angka">'.number_format($data->hargapokok,2,$decimalSep,$thousandSep).'</td>';
				$tabelpembelian .= '<td class="angka">'.number_format($subtotal,2,$decimalSep,$thousandSep).'</td>';
			}
			$tabelpembelian .= '</tr>';
		}
		$tabelpembelian .= '</tbody>';
		$tabelpembelian .= '</table><br><br>';
		print $tabelpembelian;
	}
	exit();	
}
function pembelian_produk($tgl1,$tgl2){
    get_number_format($currencySym, $thousandSep, $decimalSep, false);
	$tgl1 = date('Y-m-d', strtotime($tgl1)).' 00:00';
	$tgl2 = date('Y-m-d', strtotime($tgl2)).' 23:59';
	$tabelpembelian ='<table cellpadding="0" cellspacing="0" border="0" class="display" id="tabel_pembelian">';
	$tabelpembelian .= '<thead>';
	$tabelpembelian .= '<tr>';
	$tabelpembelian .= '<th>BARCODE</th>';
	$tabelpembelian .= '<th>PRODUK</th>';
	$tabelpembelian .= '<th>SUPPLIER</th>';
	$tabelpembelian .= '<th class="qty">QTY</th>';
	if (cekUserRoles()){
		$tabelpembelian .= '<th>H.MODAL</th>';
		$tabelpembelian .= '<th>SUBTOTAL</th>';
	}
	$tabelpembelian .= '</tr>';
	$tabelpembelian .= '</thead>';
	$tabelpembelian .= '<tbody>';
	$result = db_query("SELECT d.namasupplier, a.tglpembelian, c.barcode, c.namaproduct, SUM(b.jumlah) AS totalqty,
	c.hargapokok FROM
	pembelian a LEFT JOIN detailpembelian b ON a.idpembelian=b.idpembelian
	LEFT JOIN product c ON b.idproduct=c.idproduct
	LEFT JOIN supplier d ON c.idsupplier=d.idsupplier
	WHERE a.tglpembelian BETWEEN '%s' AND '%s' GROUP BY b.idproduct",$tgl1,$tgl2);
	$totalmodal = 0;
	while($data = db_fetch_object($result)){
		$tabelpembelian .= '<tr>';
		$tabelpembelian .= '<td>'.$data->barcode.'</td>';
		$tabelpembelian .= '<td>'.$data->namaproduct.'</td>';
		$tabelpembelian .= '<td>'.$data->namasupplier.'</td>';
		$tabelpembelian .= '<td class="angka">'.$data->totalqty.'</td>';
        $subtotal = 0;
		if (cekUserRoles()){
            $subtotal = $data->hargapokok * $data->totalqty;
			$tabelpembelian .= '<td class="angka">'.number_format($data->hargapokok,2,$decimalSep,$thousandSep).'</td>';
			$tabelpembelian .= '<td class="angka">'.number_format($subtotal,2,$decimalSep,$thousandSep).'</td>';
		}
		$tabelpembelian .= '</tr>';
		$totalmodal = $totalmodal + $subtotal;
	}
	$tabelpembelian .= '</tbody>';
    get_number_format($currencySym, $thousandSep, $decimalSep, false);
	if (cekUserRoles()){
		$tabelpembelian .= '<tfoot>';
		$tabelpembelian .= '<tr>';
		$tabelpembelian .= '<th style="text-align:right" colspan="5">Total:&nbsp;&nbsp;</th>';
		$tabelpembelian .= '<th style="text-align: right">'.$currencySym.' '.number_format($totalmodal,2,$decimalSep,$thousandSep).'&nbsp;&nbsp;</th>';
		$tabelpembelian .= '</tr>';
		$tabelpembelian .= '</tfoot>';
	}
	$tabelpembelian .= '</table>';
	return $tabelpembelian;	
}

function DateAdd($v,$d=null , $f="m/d/Y"){ 
 /*
 To Use
 $TGLHITUNG = date("m/d/Y");
 $TGLAKHIRHITUNG = DateAdd(30,$TGLHITUNG);
 */	
 $d=($d?$d:date("Y-m-d")); 
 return date($f,strtotime($v." days",strtotime($d))); 
}