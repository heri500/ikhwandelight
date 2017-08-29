var oTable;
var oTable2;
var oTable3;
var oTable4;
var oTable5;
var pathutama = '';
var pathfile = '';
var alamatupdate = '';
var currency_symbol = '';
var thousan_sep = '.';
var decimal_sep = ',';

function addCommas(nStr){
    nStr += "";
    x = nStr.split(".");
    x1 = x[0];
    x2 = x.length > 1 ? decimal_sep + x[1] : "";
    var rgx = /(\d+)(\d{3})/;
    while (rgx.test(x1)) {
        x1 = x1.replace(rgx, "$1" + thousan_sep + "$2");
    }
    return x1 + x2;
}
function tampilkantabelpelanggan(){
    oTable = $('#tabel_pelanggan').DataTable( {
        'bJQueryUI': true,
        'bAutoWidth': false,
        'lengthMenu': [[25, 50, 100, -1], [25, 50, 100, 'All']],
        'processing': true,
        'serverSide': true,
        'aoColumnDefs': [
            { 'bSortable': false, 'aTargets': [ 0,1,2 ] }
        ],
        'aaSorting': [[3, 'asc']],
        'ajax': Drupal.settings.basePath + 'sites/all/modules/datapelanggan/server_processing.php?request_data=pelanggan',
        'createdRow': function ( row, data, index ) {
            row.id = data[(data.length - 1)];
            $('td', row).eq(3).addClass('editable').editable(alamatupdate, {
                'submitdata': function ( value, settings ) {
                    return { 'row_id': this.parentNode.getAttribute('id'), 'kol_id': 3 };
                },
                'height': '20px',
                'submit': 'Ok',
                'cancel': 'Batal',
                'indicator': 'Menyimpan...',
                'tooltip': 'Klik untuk mengubah...'
            });
            $('td', row).eq(4).addClass('editable').editable(alamatupdate, {
                'submitdata': function ( value, settings ) {
                    return { 'row_id': this.parentNode.getAttribute('id'), 'kol_id': 4 };
                },
                'height': '20px',
                'submit': 'Ok',
                'cancel': 'Batal',
                'indicator': 'Menyimpan...',
                'tooltip': 'Klik untuk mengubah...'
            });
            $('td', row).eq(5).addClass('editable').editable(alamatupdate, {
                'submitdata': function ( value, settings ) {
                    return { 'row_id': this.parentNode.getAttribute('id'), 'kol_id': 5 };
                },
                'height': '20px',
                'submit': 'Ok',
                'cancel': 'Batal',
                'indicator': 'Menyimpan...',
                'tooltip': 'Klik untuk mengubah...'
            });
            $('td', row).eq(6).addClass('editable').editable(alamatupdate, {
                'submitdata': function ( value, settings ) {
                    return { 'row_id': this.parentNode.getAttribute('id'), 'kol_id': 6 };
                },
                'height': '20px',
                'submit': 'Ok',
                'cancel': 'Batal',
                'indicator': 'Menyimpan...',
                'tooltip': 'Klik untuk mengubah...'
            });
            $('td', row).eq(7).addClass('editable').editable(alamatupdate, {
                'submitdata': function ( value, settings ) {
                    return { 'row_id': this.parentNode.getAttribute('id'), 'kol_id': 7 };
                },
                'height': '20px',
                'submit': 'Ok',
                'cancel': 'Batal',
                'indicator': 'Menyimpan...',
                'tooltip': 'Klik untuk mengubah...'
            });
            $('td', row).eq(8).addClass('angka');
            $('td', row).eq(9).addClass('angka');
            $('td', row).eq(10).addClass('center');
        },
        buttons: [
            'copy', 'excel', 'print'
        ],
        'sDom': '<"button-div"B><"H"lfr>t<"F"ip>',
    });
}
function tampiltabelhutangdetail(){
    oTable2 = $('#tabel_detail_hutang').dataTable( {
        'bJQueryUI': true,
        'bAutoWidth': false,
        'bPaginate': false,
        'bLengthChange': false,
        'bFilter': true,
        'bInfo': false,
        'scrollY': '330px',
        'scrollCollapse': true,
        'aoColumnDefs': [
            { 'bSortable': false, 'aTargets': [ 0 ] }
        ],
        'aaSorting': [[1, 'asc']],
        'sDom': '<"H"<"toolbar">fr>t<"F"ip>'
    });
}
function view_detail_hutang(idpelanggan,namapelanggan,besarhutang){
    var tampilhutang = 'HUTANG SAAT INI : '+ currency_symbol +' '+ addCommas(besarhutang);
    $('#tempatnilaihutang').html(tampilhutang);
    var request = new Object();
    request.idpelanggan = idpelanggan;
    alamat = pathutama + 'datapelanggan/detailhutang';
    $.ajax({
        type: 'POST',
        url: alamat,
        data: request,
        cache: false,
        success: function(data){
            $('#detailpiutang').html(data);
            alamat = pathutama + 'datapelanggan/detailpembayaran';
            $.ajax({
                type: 'POST',
                url: alamat,
                data: request,
                cache: false,
                success: function(data2){
                    $('#detailpembayaran').html(data2);
                    $('#dialogdetailhutang').dialog('open');
                    tampiltabelhutangdetail();
                    $('div.toolbar').html('PELANGGAN : '+ namapelanggan);
                    tampiltabelpembayaran();
                    $('div.toolbar2').html('PEMBAYARAN');
                }
            });
        }
    });
}
function tampiltabeljualdetail(idpenjualan){
    oTable3 = $('#tabel_detail_penjualan').dataTable( {
        'bJQueryUI': true,
        'bAutoWidth': false,
        'sPaginationType': 'full_numbers',
        'bInfo': true,
        'aLengthMenu': [[100, 200, 300, -1], [100, 200, 300, 'All']],
        'iDisplayLength': -1,
        'bInfo': true,
        'aaSorting': [[1, 'asc']],
        'scrollY': '330px',
        'scrollCollapse': true,
        'aoColumnDefs': [
            { 'bSortable': false, 'aTargets': [ 0 ] }
        ],
        'processing': true,
        'serverSide': true,
        'ajax': Drupal.settings.basePath + 'sites/all/modules/datapelanggan/server_processing.php?request_data=detailpenjualan&idpenjualan=' + idpenjualan + '&length=-1',
        'createdRow': function ( row, data, index ) {
            row.id = data[(data.length - 1)];
            $('td', row).eq(1).addClass('center');
            $('td', row).eq(3).addClass('angka');
            $('td', row).eq(4).addClass('angka');
            $('td', row).eq(5).addClass('angka');
            $('td', row).eq(6).addClass('angka');
            $('td', row).eq(7).addClass('angka');
            $('td', row).eq(8).addClass('angka');
        },
        'footerCallback': function ( row, data, start, end, display ) {
            var api = this.api(), data;
            // Remove the formatting to get integer data for summation
            var intVal = function ( i ) {
                if (typeof i === 'string') {
                    i = i.split(thousan_sep).join('');
                    i = i.split(decimal_sep).join('.');
                }else if (typeof i === 'number'){
                    i = i;
                }else{
                    i = 0;
                }
                return parseFloat(i);
            };
            // Total over all pages
            total = api
                .column( 6 )
                .data()
                .reduce( function (a, b) {
                    return intVal(a) + intVal(b);
                }, 0 );
            // Update footer
            $( api.column( 6 ).footer() ).html(
                currency_symbol +' '+ addCommas(total)
            ).addClass('angka');
            total = api
                .column( 7 )
                .data()
                .reduce( function (a, b) {
                    return intVal(a) + intVal(b);
                }, 0 );
            // Update footer
            $( api.column( 7 ).footer() ).html(
                currency_symbol +' '+ addCommas(total)
            ).addClass('angka');
            total = api
                .column( 8 )
                .data()
                .reduce( function (a, b) {
                    return intVal(a) + intVal(b);
                }, 0 );
            // Update footer
            $( api.column( 8 ).footer() ).html(
                currency_symbol +' '+ addCommas(total)
            ).addClass('angka');
        },
    });
}
function tampiltabelpembayaran(){
    oTable4 = $('#history_pembayaran').dataTable( {
        'bJQueryUI': true,
        'bAutoWidth': false,
        'bPaginate': false,
        'bLengthChange': false,
        'scrollY': '330px',
        'scrollCollapse': true,
        'bInfo': false,
        'bFilter': true,
        'aaSorting': [[0, 'asc']],
        'sDom': '<"H"<"toolbar2">fr>t<"F"ip>'
});
}
function tampiltabeldiskon(){
    oTable5 = $('#tabel_diskon').dataTable( {
        'bJQueryUI': true,
        'bAutoWidth': false,
        'bPaginate': false,
        'bLengthChange': false,
        'bInfo': false,
        'bFilter': false,
        'aaSorting': [[0, 'asc']],
        'sDom': '<"H"<"toolbar3">fr>t<"F"ip>'
});
}
function view_detail(idpenjualan,nonota){
    var request = new Object();
    request.idpenjualan = idpenjualan;
    alamat = pathutama + 'penjualan/detailpenjualan';
    $.ajax({
        type: 'POST',
        url: alamat,
        data: request,
        cache: false,
        success: function(data){
            $('#dialogdetail').html(data);
            tampiltabeljualdetail(idpenjualan);
            $('div.toolbar').html('No. Nota : '+ nonota);
            $('#dialogdetail').dialog('open');
        }
    });
}
function pembayaran(idpelanggan,namapelanggan,besarhutang,nilaihutang){
    var tampilhutang = 'HUTANG '+ namapelanggan +' SAAT INI : '+ currency_symbol +' '+ besarhutang;
    $('#nilaipembayaran').val(parseFloat(nilaihutang));
    $('#tothutang').val(parseFloat(nilaihutang));
    $('#idpelangganbayar').val(idpelanggan);
    $('#totalhutangpelanggan').html(tampilhutang);
    $('#dialogpembayaran').dialog('open');
}
function do_pembayaran(){
    /*idpelanggan, nilaisebelumbayar, pembayaran, uid, tglbayar*/
    var request = new Object();
    request.idpelanggan = $('#idpelangganbayar').val();
    request.hutang = $('#tothutang').val();
    request.pembayaran = $('#nilaipembayaran').val();
    request.tglbayar = $('#tglbayarkirim').val();
    request.keterangan = $('#keterangan').val();
    alamat = pathutama + 'datapelanggan/pembayaran';
    $.ajax({
        type: 'POST',
        url: alamat,
        data: request,
        cache: false,
        success: function(){
            window.location = pathutama + 'datapelanggan/pelanggan';
        }
    });
}
function tabeldiskon(idpelanggan,namapelanggan){
    var request = new Object();
    request.idpelanggan = idpelanggan;
    request.namapelanggan = namapelanggan;
    alamat = pathutama + 'datapelanggan/tabeldiskon';
    $.ajax({
        type: 'POST',
        url: alamat,
        data: request,
        cache: false,
        success: function(data){
            $('#idpelanggan').val(idpelanggan);
            $('#tabeldiskon').html(data);
            tampiltabeldiskon();
            $('div.toolbar3').html('PELANGGAN : '+ namapelanggan);
            $('#diskonpelanggan').dialog('open');
            $('#namapelanggandiskon').val(namapelanggan);
        }
    });
}
function tambahdiskon(){
    if ($('#idpelanggan').val() > 0 && $('#diskon').val() >= 0){
        var request = new Object();
        request.idpelanggan = $('#idpelanggan').val();
        request.idkategori = $('#idkategori').val();
        request.diskon = $('#diskon').val();
        alamat = pathutama + 'datapelanggan/simpandiskon';
        $.ajax({
            type: 'POST',
            url: alamat,
            data: request,
            cache: false,
            success: function(data){
                var request2 = new Object();
                request2.idpelanggan = $('#idpelanggan').val();
                request2.namapelanggan = $('#namapelanggandiskon').val();
                alamat = pathutama + 'datapelanggan/tabeldiskon';
                $.ajax({
                    type: 'POST',
                    url: alamat,
                    data: request,
                    cache: false,
                    success: function(data){
                        $('#tabeldiskon').html(data);
                        tampiltabeldiskon();
                        $('div.toolbar3').html('PELANGGAN : '+ $('#namapelanggandiskon').val());
                        $('#diskon').select();
                    }
                });
            }
        });
    }
}
function hapus_diskon(idpelanggan, idkategori, namapelanggan){
    var tanya = confirm('Apakah diskon ini benar-benar ingin dihapus..??');
    if (tanya != 0){
        var request = new Object();
        request.idpelanggan = idpelanggan;
        request.idkategori = idkategori;
        alamat = pathutama + 'datapelanggan/hapusdiskon';
        $.ajax({
            type: 'POST',
            url: alamat,
            data: request,
            cache: false,
            success: function(data){
                var request2 = new Object();
                request2.idpelanggan = $('#idpelanggan').val();
                request2.namapelanggan = namapelanggan;
                alamat = pathutama + 'datapelanggan/tabeldiskon';
                $.ajax({
                    type: 'POST',
                    url: alamat,
                    data: request,
                    cache: false,
                    success: function(data){
                        $('#tabeldiskon').html(data);
                        tampiltabeldiskon();
                        $('div.toolbar3').html('PELANGGAN : '+ namapelanggan);
                        $('#diskon').select();
                    }
                });
            }
        });
    }
}
$(document).ready(function() {
    pathutama = Drupal.settings.basePath;
    pathfile = pathutama + Drupal.settings.filepath;
    alamatupdate = pathutama + 'datapelanggan/updatepelanggan';
    currency_symbol = Drupal.settings.datapremis.currency_symbol;
    thousan_sep = Drupal.settings.datapremis.thousand_separator;
    decimal_sep = Drupal.settings.datapremis.decimal_separator;
    $('#tabel_pelanggan tbody .editable').editable(alamatupdate, {
        'callback': function( sValue, y ) {
            var aPos = oTable.fnGetPosition( this );
            oTable.fnUpdate( sValue, aPos[0], aPos[1] );
        },
        'submitdata': function ( value, settings ) {
            var aPos = oTable.fnGetPosition( this );
            return { 'row_id': this.parentNode.getAttribute('id'), 'kol_id': aPos[1] };
        },
        'height': '20px',
        'submit': 'Ok',
        'cancel': 'Batal',
        'indicator': 'Menyimpan...',
        'tooltip': 'Klik untuk mengubah...'
    });
    tampilkantabelpelanggan();
    $('#formpelanggan').validationEngine();
    $('button').button();
    $('#kodepelanggan').autotab_filter({
        format: 'alphanumeric',
        uppercase: true,
        nospace: true
    });
    $('#dialogdetailhutang').dialog({
        modal: true,
        width: 980,
        resizable: false,
        autoOpen: false,
        position: ['auto','auto']
    });
    $('#dialogdetail').dialog({
        modal: true,
        width: 850,
        resizable: false,
        autoOpen: false,
        position: ['auto','auto']
    });
    $('#dialogpembayaran').dialog({
        modal: true,
        width: 450,
        resizable: false,
        autoOpen: false,
        position: ['auto','auto'],
        open: function(event, ui) {
            $('#nilaipembayaran').focus();
            $('#nilaipembayaran').select();
        }
    });
    $('#diskonpelanggan').dialog({
        modal: true,
        width: 650,
        resizable: false,
        autoOpen: false,
        position: ['auto','auto'],
        open: function(event, ui) {
            $('#diskon').focus();
            $('#diskon').select();
        }
    });
    $('#tglbayar').datepicker({
        changeMonth: true,
        changeYear: true,
        dateFormat: 'dd-mm-yy',
        altField: '#tglkirim',
        altFormat: 'yy-mm-dd'
    });
    $('#nilaipembayaran').keypress(function(e) {
        if (e.keyCode == 13){
            $('#bayarhutang').click();
        }
    });
    $('#sync-hutang-pelanggan').on('click', function(){
        alamat = pathutama + 'datapelanggan/synchutangpelanggan';
        $.ajax({
            type: 'POST',
            url: alamat,
            cache: false,
            success: function(){
                oTable.draw(false);
            }
        });
    });
})