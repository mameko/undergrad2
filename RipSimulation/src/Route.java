import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TimerTask;

/**
 * ·������
 * 
 * @author Administrator
 * 
 */
public class Route extends TimerTask {
	String rNameString = new String();// ·�ɵ�����
	Map<String, RInfo> rForm = new HashMap<String, RInfo>();// ·�ɱ�
	List<Route> rRelateList = new ArrayList<Route>();// ��¼����·�����ı�
	Map<String, RInfo> rFormfromOutside = new HashMap<String, RInfo>();

	public void receive() {// ÿ��30secȥ��һ������·�ɵ�rForm
		for (int i = 0; i < rRelateList.size(); i++) {
			renewRForm(rRelateList.get(i));// ÿ�ζ��������Լ���·�ɱ�
		}
	}

	public void renewRForm(Route routeLearn) {// �����Լ���rForm��ÿ�θ��µ�ʱ����RInfo��lastVisit�ֶΣ�����и��µĻ���lastVisit���㣬
		// û�еĻ��Ͱ�ԭ�������ּ�1��������ֵ���6�Ļ�����ʾ180secû���յ����ڸ�����¼����Ϣ����distance�����룩��Ϊ16���ɴ
		// ������ֵ���10�Ļ�����ʾ�Ѿ��ٹ���120sec�˵�����û�й��ڸ�����¼����Ϣ��ɾ������·�ɼ�¼
		Set<String> destinSet = routeLearn.rForm.keySet();
		for (Iterator iterator = destinSet.iterator(); iterator.hasNext();) {//����·�ɱ�
			String destinString = (String) iterator.next();
			RInfo rInfoLearn = new RInfo();
			RInfo rInfoSelf = new RInfo();
			if (this.rForm.containsKey(destinString)) {// �������ͬ��·����Ϣ
				rInfoSelf = this.rForm.get(destinString);
				rInfoLearn = routeLearn.rForm.get(destinString);
				if (rInfoLearn.distance < rInfoSelf.distance - 1) {// ���ѧϰ������·����Ϣ���Լ����еĸ���Ч
					rInfoLearn.distance = rInfoLearn.distance + 1;
					if (rInfoLearn.distance>15) {
						rInfoLearn.distance = 16;
					}
					rInfoLearn.nextHopString = routeLearn.rNameString;
					this.rForm.put(destinString, rInfoLearn);
				} else {// ������Ǹ���Ч�Ͳ�����					
				}
			} else {//���û�еĻ�����ѧϰ��������Ϣ���뵽�Լ���·�ɱ���
				rInfoLearn = routeLearn.rForm.get(destinString);
				rInfoLearn.distance = rInfoLearn.distance + 1;
				if (rInfoLearn.distance>15) {
					rInfoLearn.distance = 16;
				}
				rInfoLearn.nextHopString = routeLearn.rNameString;
				this.rForm.put(destinString, rInfoLearn);				
			}
		}
		Set<String> destinSetSelf = this.rForm.keySet();//��������destinsetself - destinset�����·�ɱ���ĸ�����Ϣ
		for (Iterator iterator = destinSetSelf.iterator(); iterator.hasNext();) {
			String desSelfString = (String) iterator.next();
			if (!routeLearn.rForm.containsKey(desSelfString)) {
				RInfo rInfoToChange = new RInfo();
				rInfoToChange = this.rForm.get(desSelfString);
				rInfoToChange.lastRefresh = rInfoToChange.lastRefresh + 1;
				if (rInfoToChange.lastRefresh == 6) {//���ڵ���6��С��10
					rInfoToChange.distance = 16;
					this.rForm.put(desSelfString, rInfoToChange);
				}else {
					if (rInfoToChange.distance == 10) {
						this.rForm.remove(desSelfString);
					}else {
						this.rForm.put(desSelfString, rInfoToChange);//С��6	
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
