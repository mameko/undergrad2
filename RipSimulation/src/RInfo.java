/**
 * ·�ɱ����ĺ�벿��
 * @author Administrator
 *
 */
public class RInfo {
	int lastRefresh = 0;//���ǰ�����¹�����30secΪ��λ�������º�����
	int distance = 0;//������С��16�����ھͲ��ɴ���
	String nextHopString = "";//��һ��Ҫͨ���ĸ�·��ȥĿ������
//	String learnFromString = "";//������¼�Ǵ��ĸ�·��ѧ�����ģ�����ʵ�ִ�������ת��ˮƽ�ָ�
	public int getLastRefresh() {
		return lastRefresh;
	}
	public void setLastRefresh(int lastRefresh) {
		this.lastRefresh = lastRefresh;
	}
	public int getDistance() {
		return distance;
	}
	public void setDistance(int distance) {
		this.distance = distance;
	}
	public String getNextHopString() {
		return nextHopString;
	}
	public void setNextHopString(String nextHopString) {
		this.nextHopString = nextHopString;
	}	
}
