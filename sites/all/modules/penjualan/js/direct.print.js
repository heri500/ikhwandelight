$(document).ready(function(){
	jsPrintSetup.setOption('orientation', jsPrintSetup.kPortraitOrientation);
	jsPrintSetup.setOption('marginTop', 0);
	jsPrintSetup.setOption('marginBottom', 0);
	jsPrintSetup.setOption('marginLeft', 0);
	jsPrintSetup.setOption('marginRight', 0);
	// Suppress print dialog
	jsPrintSetup.setSilentPrint(true);/** Set silent printing */
	// Do Print
	jsPrintSetup.print();
	close();
	// Restore print dialog
	//jsPrintSetup.setSilentPrint(false);
});