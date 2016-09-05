public class PhraseOMatic{
	public static void main(String[] args){
		String[] wordListOne = { "24/7","multi-Tier","30,000"};
		int oneLength = wordListOne.length;
		int rand1 = (int) (Math.random() * oneLength);
		String phrase = wordListOne[rand1];
		System.out.println("the word is :" +phrase);
	}
} 