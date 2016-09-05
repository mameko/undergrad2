import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TimerTask;

/**
 * 路由器类
 * 
 * @author Administrator
 * 
 */
public class Route extends TimerTask {
	String rNameString = new String();// 路由的名字
	Map<String, RInfo> rForm = new HashMap<String, RInfo>();// 路由表
	List<Route> rRelateList = new ArrayList<Route>();// 记录相邻路由器的表
	Map<String, RInfo> rFormfromOutside = new HashMap<String, RInfo>();

	public void receive() {// 每隔30sec去读一次相邻路由的rForm
		for (int i = 0; i < rRelateList.size(); i++) {
			renewRForm(rRelateList.get(i));// 每次读完后更新自己的路由表
		}
	}

	public void renewRForm(Route routeLearn) {// 更新自己的rForm，每次更新的时候检查RInfo的lastVisit字段，如果有更新的话把lastVisit置零，
		// 没有的话就把原来的数字加1，如果数字等于6的话即表示180sec没有收到关于该条记录的信息，把distance（距离）设为16不可达；
		// 如果数字等于10的话即表示已经再过了120sec了但还是没有关于该条记录的信息，删除该条路由记录
		Set<String> destinSet = routeLearn.rForm.keySet();
		for (Iterator iterator = destinSet.iterator(); iterator.hasNext();) {//更新路由表
			String destinString = (String) iterator.next();
			RInfo rInfoLearn = new RInfo();
			RInfo rInfoSelf = new RInfo();
			if (this.rForm.containsKey(destinString)) {// 如果有相同的路由信息
				rInfoSelf = this.rForm.get(destinString);
				rInfoLearn = routeLearn.rForm.get(destinString);
				if (rInfoLearn.distance < rInfoSelf.distance - 1) {// 如果学习得来的路由信息比自己所有的更有效
					rInfoLearn.distance = rInfoLearn.distance + 1;
					if (rInfoLearn.distance>15) {
						rInfoLearn.distance = 16;
					}
					rInfoLearn.nextHopString = routeLearn.rNameString;
					this.rForm.put(destinString, rInfoLearn);
				} else {// 如果不是更有效就不理它					
				}
			} else {//如果没有的话，就学习，即把信息加入到自己的路由表中
				rInfoLearn = routeLearn.rForm.get(destinString);
				rInfoLearn.distance = rInfoLearn.distance + 1;
				if (rInfoLearn.distance>15) {
					rInfoLearn.distance = 16;
				}
				rInfoLearn.nextHopString = routeLearn.rNameString;
				this.rForm.put(destinString, rInfoLearn);				
			}
		}
		Set<String> destinSetSelf = this.rForm.keySet();//下面求差集，destinsetself - destinset，求出路由表项的更新信息
		for (Iterator iterator = destinSetSelf.iterator(); iterator.hasNext();) {
			String desSelfString = (String) iterator.next();
			if (!routeLearn.rForm.containsKey(desSelfString)) {
				RInfo rInfoToChange = new RInfo();
				rInfoToChange = this.rForm.get(desSelfString);
				rInfoToChange.lastRefresh = rInfoToChange.lastRefresh + 1;
				if (rInfoToChange.lastRefresh == 6) {//大于等于6，小于10
					rInfoToChange.distance = 16;
					this.rForm.put(desSelfString, rInfoToChange);
				}else {
					if (rInfoToChange.distance == 10) {
						this.rForm.remove(desSelfString);
					}else {
						this.rForm.put(desSelfString, rInfoToChange);//小于6	
					}
				}				
			}
			
		}
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		receive();
	}

}
