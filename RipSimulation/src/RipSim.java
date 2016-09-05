import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.Timer;

public class RipSim {

	/**
	 * 模拟rip的主程序
	 * 
	 * @param args
	 */

	static Map<String, Route> routeList = new HashMap<String, Route>();// 系统在这次模拟中所涉及的路由

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("please input route's number:");// 让用户输入系统中有多少个路由
		InputHelper helper = new InputHelper();
		String rNumberString = helper.inputHelper();
		int rnum = Integer.parseInt(rNumberString);
		for (int i = 0; i < rnum; i++) {// 设置好没个路由的初始信息
			Route route = new Route();
			route.rNameString = "r" + String.valueOf(i + 1);

			// 设置好此路由的路由表的初始状态，ie，只有与它直接相连的网络的路由信息，距离distance为0。这里由用户自己选择该路由器与
			System.out.println("plese input the directed connected network of "
					+ route.rNameString + "(split with space) : ");
			String stringToSplitNetwork = helper.inputHelper();
			String[] directRelatedN = stringToSplitNetwork.split(" ");
			for (int k = 0; k < directRelatedN.length; k++) {
				RInfo rInfo = new RInfo();// 直接相连的网络。
				rInfo.distance = 0;
				rInfo.lastRefresh = 0;
				route.rForm.put(directRelatedN[k], rInfo);
			}
			routeList.put(route.rNameString, route);
		}
		// 设置每个路由的相邻路由
		for (int i = 0; i < rnum; i++) {
			int k = i + 1;
			System.out
					.println("please choose r"
							+ k
							+ " is connected with which route(split with space like:1 2) : ");// 设置好相邻的路由
			String stringToSplitRoute = helper.inputHelper();
			String[] relatedR = stringToSplitRoute.split(" ");// 用空格分开输入相邻的路由
			List<Route> rRelateList = new ArrayList<Route>();
			for (int j = 0; j < relatedR.length; j++) {
				Route route = new Route();
				if (i != Integer.parseInt(relatedR[j]) - 1) {
					route = routeList.get(String.valueOf("r" + relatedR[j]));
				}
				rRelateList.add(route);
			}
			Route route2 = new Route();
			route2 = routeList.get("r" + String.valueOf(i + 1));
			route2.rRelateList = rRelateList;
			routeList.put("r" + String.valueOf(i + 1), route2);
		}

		// 下面开始运行路由让路由互相学习
		Collection<Route> routes = routeList.values();
		for (Iterator iterator = routes.iterator(); iterator.hasNext();) {
			Route route = (Route) iterator.next();
			Timer timer = new Timer();
			timer.schedule(route, 30000, 30000);// 循环把所有路由叫起来，然后设置没30sec更新一次
		}

		// 以下是，在实验开始了一段时间后观察路由表情况的功能段
		String check = "";
		while (check.equals("")) {
			System.out
					.println("enter 'check' to see all the route table(if you want to quit, enter 'quit') : ");
			check = helper.inputHelper();
			if (!check.equals("quit")) {
				if (check.equals("check")) {
					// 显示各个路由信息
					Collection<Route> routes2 = routeList.values();
					for (Iterator iterator = routes2.iterator(); iterator
							.hasNext();) {
						Route route2 = (Route) iterator.next();
						Set<String> r2KeySet = route2.rForm.keySet();
						System.out.println("");
						System.out.println(route2.rNameString);
						System.out.println("----------------------");
						System.out.println("| 目的网络 | 距离 | 路由 |");
						for (Iterator iterator2 = r2KeySet.iterator(); iterator2
								.hasNext();) {
							String keyString = (String) iterator2.next();
							System.out.print("|" + keyString + "| ");
							RInfo rInfo = new RInfo();
							rInfo = route2.rForm.get(keyString);
							System.out.print(rInfo.distance + " | ");
							System.out.println(rInfo.nextHopString + " |");
						}
						System.out.println("----------------------");
					}
					check = "";
				}
			}
			System.exit(0);
		}
	}
}
