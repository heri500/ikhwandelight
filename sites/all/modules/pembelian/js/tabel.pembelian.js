var oTable;
var pathutama = '';
var urutan = '';
var alamatupdatetanggalbeli = '';

function tampiltabelbeli(){
	oTable = $("#tabel_pembelian").dataTable( {
		"bJQueryUI": true,
		"bAutoWidth": false,
		"sPaginationType": "full_numbers",
		"bInfo": false,
		"aLengthMenu": [[100, 200, 300, -1], [100, 200, 300, "All"]],
		"iDisplayLength": 100,
		"aaSorting": [[ 2 , "desc"]],
		"sDom": '<"space"T><C><"clear"><"H"lfr>t<"F"ip>',
		"oColVis": {
			"activate": "mouseover",
			'aiExclude': [ 0,1 ]
		},
		"aoColumnDefs": [
			{ "bSortable": false, "aTargets": [ 0,1,3 ] }
		]
	});
}
function tampiltabelbelidetail(){
	oTable = $("#tabel_detail_pembelian").dataTable( {
		"bJQueryUI": true,
		"bAutoWidth": false,
		"bPaginate": false,
		"bLengthChange": false,
		"bInfo": false,
		"aaSorting": [[0, "asc"]],
		"sDom": '<"H"<"toolbar">fr>t<"F"ip>'
	});
}
function view_detail(idpembelian,nonota){
	var request = new Object();
	request.idpembelian = idpembelian;
	alamat = pathutama + "pembelian/detailpembelian";
	$.ajax({
		type: "POST",
		url: alamat,
		data: request,
		cache: false,
		success: function(data){
			$("#dialogdetail").html(data);
			tampiltabelbelidetail();
			$("div.toolbar").html("No. Nota : "+ nonota);
			$("#dialogdetail").dialog("open");
		}
	});
}
function delete_pembelian(idpembelian,nonota){
	var konfirmasi = confirm('Yakin ingin menghapus pembelian dengan no nota : '+ nonota +' ini...??!!');	
	if (konfirmasi){
		window.location = pathutama + 'pembelian/deletepembelian/'+ idpembelian +'?destination=pembelian/viewpembelian';	
	}
}
$(document).ready(function(){
	pathutama = Drupal.settings.basePath;
	alamatupdatetanggalbeli = pathutama + 'pembelian/updatepembelian';
	urutan = Drupal.settings.urutan;
	$("#dialogdetail").dialog({
		modal: true,
		width: 850,
		resizable: false,
		autoOpen: false,
		position: ["auto","auto"]
	});
	$("button").button();
	TableToolsInit.sSwfPath = pathutama +"misc/media/datatables/swf/ZeroClipboard.swf";
	if (urutan == 1){
		$('.edit-tanggal').editable(alamatupdatetanggalbeli,{
			submitdata : function(value, settings) {
			 var idpembelian = $(this).attr('id');
			 var splitidpembelian = idpembelian.split('-');
			 idpembelian = splitidpembelian[1];
			 var jampembelianupdate = $('#jampembelian-'+ idpembelian).html();
			 return {jampembelian: jampembelianupdate,ubah: 'tanggal'};
   		},
			name : 'tanggalbeli',
			width : 130,
			height : 18,
			style   : 'margin: 0',
			tooltip   : 'Klik untuk mengubah tanggal pembelian',
	    indicator : 'Saving...',
	    type: "datepicker",
			datepicker: {
	      changeMonth: true,
	      changeYear: true,
	      dateFormat: "dd-mm-yy"
	    },
	    callback : function(value, settings) {
      	var split_tanggal = value.split('-');
      	var tanggalbeli = new Date();
      	var bulan = parseInt(split_tanggal[1]) - 1;
				tanggalbeli.setFullYear(split_tanggal[2],bulan,split_tanggal[0]);
				var indexhari = tanggalbeli.getDay();
				var hari = Drupal.settings.namahari[indexhari];
				var idpembelian = $(this).attr('id');
			 	var splitidpembelian = idpembelian.split('-');
			 	idpembelian = splitidpembelian[1];
			 	$('#haripembelian-'+ idpembelian).html(hari);
     	}
	  });
	  $('.edit-jam').editable(alamatupdatetanggalbeli,{
			name : 'jampembelian',
			width : 120,
			height : 18,
			style   : 'margin: 0;',
			type: "timepicker",
			submitdata : function(value, settings) {
			 var idpembelian = $(this).attr('id');
			 var splitidpembelian = idpembelian.split('-');
			 idpembelian = splitidpembelian[1];
			 var tglpembelianupdate = $('#tglpembelian-'+ idpembelian).html();
			 return {tanggalbeli: tglpembelianupdate,ubah: 'jam'};
   		},
			timepicker: {
		  	timeOnlyTitle: "PILIH WAKTU",
				timeText: "Waktu",
				hourText: "Jam",
				minuteText: "Menit",
				secondText: "Detik",
				currentText: "Saat Ini",
				showButtonPanel: false
		  },
		  submit		: "Ok",
			tooltip   : 'Klik untuk mengubah jam pembelian',
	    indicator : 'Saving...'
	  });
	}
	tampiltabelbeli();
	$("#tgl1").datepicker({
		changeMonth: true,
		changeYear: true,
		dateFormat: "dd-mm-yy"
	});
	$("#tgl2").datepicker({
		changeMonth: true,
		changeYear: true,
		dateFormat: "dd-mm-yy"
	});
})