
class TestGtk {
	
	static function main() {
	
		trace( "Initializing GTK ..." );
		gtk.Lib.init();
		trace( "GTK initialized." );
		
		trace( "Starting GTK loop ..." );
		gtk.Lib.run();
		
		trace( "GTK quit ..." );
		gtk.Lib.quit();
		trace( "GTK finished." );
	}
	
}
