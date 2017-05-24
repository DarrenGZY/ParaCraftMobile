--[[
Title: Main loop
Author(s): LiXizhi
Company: ParaEnging Co.
Date: 2014/3/21
Desc: Entry point and game loop
use the lib:
------------------------------------------------------------
NPL.activate("script/mobile/samples/HelloWorldMCML/main.lua");
------------------------------------------------------------
]]
-- ����һЩ�������
NPL.load("(gl)script/kids/ParaWorldCore.lua"); 
NPL.load("(gl)script/apps/IMServer/IMserver_client.lua");
-- ͨѶϵͳ
JabberClientManager = commonlib.gettable("IMServer.JabberClientManager");

-- ѡ��һ������ϵͳ��
System = commonlib.inherit(Map3DSystem);

--�������ļ�
local function load_config()
	System.options.is_client = true;
	local filename = "config/GameClient.config.xml"
	local xmlRoot = ParaXML.LuaXML_ParseFile(filename);
	if(not xmlRoot) then
		LOG.std("", "warning", "aries", "warning: failed loading game server config file %s", filename);
		return;
	end	
	local node;
	node = commonlib.XPath.selectNodes(xmlRoot, "/GameClient/asset_server_addresses/address")[1];
	if(node and node.attr) then
		-- ������Դ������URL
		ParaAsset.SetAssetServerUrl(node.attr.host);
		LOG.std("", "system", "aries", "Asset server: %s", node.attr.host)
	end
end

-- ��ʼ������
local function InitApp()
	--�������ļ�
	load_config();

	--��ʼ��ϵͳ
	main_state = System.init();

	-- ʹ��һ��Creator��������GUIƤ��
	NPL.load("(gl)script/apps/Aries/Creator/Game/DefaultTheme.mc.lua");
	MyCompany.Aries.Creator.Game.Theme.Default:Load();

	-- ע��һЩ���õ��ڲ�APP�� 
	System.App.Registration.CheckInstallApps({
		{app={app_key="WebBrowser_GUID"}, IP_file="script/kids/3DMapSystemApp/WebBrowser/IP.xml"},
		{app={app_key="worlds_GUID"}, IP_file="script/kids/3DMapSystemApp/worlds/IP.xml"},
		{app={app_key="Debug_GUID"}, IP_file="script/kids/3DMapSystemApp/DebugApp/IP.xml"},
	})

	-- ע�᳣��HTML��Ⱦ�ؼ�
	NPL.load("(gl)script/apps/Aries/mcml/mcml_aries.lua");
	MyCompany.Aries.mcml_controls.register_all();

	-- ��ʾһ��HTMLҳ��
	NPL.load("(gl)script/kids/3DMapSystemApp/mcml/PageCtrl.lua");
	local page = System.mcml.PageCtrl:new({url="script/mobile/samples/HelloWorldMCML/HelloWorld.html"});
	page:Create("helloworldpage", nil, "_fi", 0, 0, 0, 0)

	-- _guihelper.MessageBox("���������:");
end

-- ��ѭ���� ÿ������2��. 
local function activate()
	if(main_state == nil) then
		main_state = 1;
		-- ��ֻ֤����һ��
		InitApp();
	else
		
	end
end

NPL.this(activate);