class FactSwig{

	public static int fact(int x){
		if(x == 1 || x ==0) return 1;
		else return x * fact(x-1);
	}

	public static void main(String[] arg){
		for(int i = 0; i<= 50000000; i++){
			fact(5);
		}
	}
}
