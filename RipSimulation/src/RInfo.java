/**
 * 路由表的项的后半部分
 * @author Administrator
 *
 */
public class RInfo {
	int lastRefresh = 0;//多久前被更新过，以30sec为单位，被更新后清零
	int distance = 0;//跳数，小于16，大于就不可达啦
	String nextHopString = "";//下一跳要通过哪个路由去目标网络
//	String learnFromString = "";//这条记录是从哪个路由学回来的，用于实现带毒性逆转的水平分割
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
