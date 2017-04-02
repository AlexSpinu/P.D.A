
public class Main {

	public static void main(String[] args) {

		Thread prodTh = new Thread(new Producer());
		Thread consTh = new Thread(new Consumer());
		prodTh.start();
		consTh.start();
	}

}
