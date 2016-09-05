import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;


public class InputHelper {
	public String inputHelper(){
		String inputLine = "";		
		try {
			BufferedReader isBufferedReader = new BufferedReader(
					new InputStreamReader(System.in));
			inputLine = isBufferedReader.readLine();
			if (inputLine.length() == 0)
				System.out.println("input error");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return inputLine;
	}
}
