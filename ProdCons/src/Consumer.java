
public class Consumer implements Runnable {
	Queue q = new Queue();

	public void run() {
		for (int i = 0; i < 10; i++)
			q.Consume(i);
	}

}
