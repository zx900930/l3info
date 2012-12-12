class Fontionjava{
	public static void main(String [] args){
		system.loadLibrary("factlib");
		for(int i = 0; i<= 50000000; i++){
			factlib.fact(5);
		}
		system.out.println("Terminé");
	}
}
