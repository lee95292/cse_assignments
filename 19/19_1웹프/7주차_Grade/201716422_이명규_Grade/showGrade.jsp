<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="gradeManage.GradeDAO" %>
<%@ page import="gradeManage.GradeBean" %>
<%@ page import="java.util.ArrayList" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
</head>
	<%
		GradeDAO gdao = new GradeDAO();
	
		ArrayList<GradeBean> gbeanList= new ArrayList<GradeBean>();
		
		gbeanList = gdao.getGrade();
		
		for(GradeBean gbean:gbeanList){
			out.print(gbean.getName()+" ");
			out.print(gbean.getLab1()+" ");
			out.print(gbean.getLab2()+" ");
			out.print(gbean.getMidterm());
			out.print("<br>");
		}
	%>
<body>
</body>
</html>