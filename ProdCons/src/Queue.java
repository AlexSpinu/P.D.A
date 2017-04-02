import java.util.concurrent.Semaphore;

public class Queue {
	int value;

	static Semaphore Prod = new Semaphore(1);

	static Semaphore Con = new Semaphore(0);

	void Consume(int i) {
		try {
			Con.acquire();
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			System.out.println("Thread intrerrupted");
			e.printStackTrace();
		}
		System.out.println("Consumed: " + i);
		Prod.release();
	}

	void Produce(int n) {
		try {
			Prod.acquire();
			Thread.sleep(500);
		} catch (InterruptedException e) {
			System.out.println("Thread intrerrupted");
			e.printStackTrace();
		}

		this.value = n;
		System.out.println("Produced: " + n);
		Con.release();
	}
}
