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
	 * ģ��rip��������
	 * 
	 * @param args
	 */

	static Map<String, Route> routeList = new HashMap<String, Route>();// ϵͳ�����ģ�������漰��·��

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("please input route's number:");// ���û�����ϵͳ���ж��ٸ�·��
		InputHelper helper = new InputHelper();
		String rNumberString = helper.inputHelper();
		int rnum = Integer.parseInt(rNumberString);
		for (int i = 0; i < rnum; i++) {// ���ú�û��·�ɵĳ�ʼ��Ϣ
			Route route = new Route();
			route.rNameString = "r" + String.valueOf(i + 1);

			// ���úô�·�ɵ�·�ɱ�ĳ�ʼ״̬��ie��ֻ������ֱ�������������·����Ϣ������distanceΪ0���������û��Լ�ѡ���·������
			System.out.println("plese input the directed connected network of "
					+ route.rNameString + "(split with space) : ");
			String stringToSplitNetwork = helper.inputHelper();
			String[] directRelatedN = stringToSplitNetwork.split(" ");
			for (int k = 0; k < directRelatedN.length; k++) {
				RInfo rInfo = new RInfo();// ֱ�����������硣
				rInfo.distance = 0;
				rInfo.lastRefresh = 0;
				route.rForm.put(directRelatedN[k], rInfo);
			}
			routeList.put(route.rNameString, route);
		}
		// ����ÿ��·�ɵ�����·��
		for (int i = 0; i < rnum; i++) {
			int k = i + 1;
			System.out
					.println("please choose r"
							+ k
							+ " is connected with which route(split with space like:1 2) : ");// ���ú����ڵ�·��
			String stringToSplitRoute = helper.inputHelper();
			String[] relatedR = stringToSplitRoute.split(" ");// �ÿո�ֿ��������ڵ�·��
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

		// ���濪ʼ����·����·�ɻ���ѧϰ
		Collection<Route> routes = routeList.values();
		for (Iterator iterator = routes.iterator(); iterator.hasNext();) {
			Route route = (Route) iterator.next();
			Timer timer = new Timer();
			timer.schedule(route, 30000, 30000);// ѭ��������·�ɽ�������Ȼ������û30sec����һ��
		}

		// �����ǣ���ʵ�鿪ʼ��һ��ʱ���۲�·�ɱ�����Ĺ��ܶ�
		String check = "";
		while (check.equals("")) {
			System.out
					.println("enter 'check' to see all the route table(if you want to quit, enter 'quit') : ");
			check = helper.inputHelper();
			if (!check.equals("quit")) {
				if (check.equals("check")) {
					// ��ʾ����·����Ϣ
					Collection<Route> routes2 = routeList.values();
					for (Iterator iterator = routes2.iterator(); iterator
							.hasNext();) {
						Route route2 = (Route) iterator.next();
						Set<String> r2KeySet = route2.rForm.keySet();
						System.out.println("");
						System.out.println(route2.rNameString);
						System.out.println("----------------------");
						System.out.println("| Ŀ������ | ���� | ·�� |");
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
