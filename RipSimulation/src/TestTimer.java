import java.util.Timer;
import java.util.TimerTask;


public class TestTimer {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Timer timer = new Timer();
		timer.schedule(new task(), 0 ,1000);
	}
}

class task extends TimerTask{
	@Override
	public void run() {
		// TODO Auto-generated method stub
		System.out.println("pan");
	}
	
}