package com.itbaizhan.util;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
public class DBConn {
	
	
	

	
	public static String username = "root";
	public static String password = "root";
	public static String url = "jdbc:mysql://localhost:3306/flowershop?characterEncoding=utf-8&serverTimezone=GMT%2B8";
	
	private static String jdbc = "com.mysql.cj.jdbc.Driver";
	
	
	
	
	
	/**
	 * 获得数据库的连接
	 * @return
	 */
	public static Connection getConn() {
		Connection conn = null;
		try {
			Class.forName(jdbc);
			conn = DriverManager.getConnection
			(url,username,password);

		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return conn;
	}
	
	//关闭数据库的连接
	public static void close(Connection conn,PreparedStatement ps,ResultSet rs){
		if(rs!=null){
			try{
				rs.close();
			}catch(Exception e){
				
			}
		}
		
		if(ps!=null){
			try{
				ps.close();
			}catch(Exception e){
				
			}
		}
		
		if(conn!=null){
			try{
				conn.close();
			}catch(Exception e){
				
			}
		}
		
		
		
		
	}
	
	

	
}
