
class TestGtk {
	
	static function main() {
		
		trace( "Is main thread: "+gtk.Lib.isMainThread() );
		
		gtk.Lib.sync(function(){
			trace("SSYNC");
			var win = new gtk.Window("HXGtk",200,200);
			//win.show();
		});
		gtk.Lib.main();
		
		/*
		neko.vm.Ui;
		
		//trace( neko.vm.Ui.isMainThread() );
		neko.vm.Ui.loop();
*/

		/* 
		trace( "Initializing GTK ..." );
		gtk.Lib.init();
		trace( "GTK initialized." );
		
		var win = new gtk.Window("HXGtk");
		
		trace( "Starting GTK loop ..." );
		gtk.Lib.run();
		
		trace( "GTK quit ..." );
		gtk.Lib.quit();
		trace( "GTK finished." );
		*/
		
	}
	
}
